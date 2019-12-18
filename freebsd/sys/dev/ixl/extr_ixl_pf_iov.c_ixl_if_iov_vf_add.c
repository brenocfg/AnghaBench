#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
typedef  int /*<<< orphan*/  sysctl_name ;
struct TYPE_2__ {int /*<<< orphan*/  ftl; struct ixl_pf* back; } ;
struct ixl_vf {size_t vf_num; int /*<<< orphan*/  ctx; TYPE_1__ vsi; int /*<<< orphan*/  vf_flags; int /*<<< orphan*/  mac; } ;
struct ixl_pf {struct ixl_vf* vfs; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int QUEUE_NAME_LEN ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VF_FLAG_ENABLED ; 
 int /*<<< orphan*/  VF_FLAG_MAC_ANTI_SPOOF ; 
 int /*<<< orphan*/  VF_FLAG_PROMISC_CAP ; 
 int /*<<< orphan*/  VF_FLAG_SET_MAC_CAP ; 
 int /*<<< orphan*/  VF_FLAG_VLAN_CAP ; 
 int /*<<< orphan*/  bcopy (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ixl_pf* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_add_vsi_sysctls (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ixl_reset_vf (struct ixl_pf*,struct ixl_vf*) ; 
 int ixl_vf_reserve_queues (struct ixl_pf*,struct ixl_vf*,int) ; 
 int ixl_vf_setup_vsi (struct ixl_pf*,struct ixl_vf*) ; 
 scalar_t__ nvlist_exists_binary (int /*<<< orphan*/  const*,char*) ; 
 void* nvlist_get_binary (int /*<<< orphan*/  const*,char*,size_t*) ; 
 scalar_t__ nvlist_get_bool (int /*<<< orphan*/  const*,char*) ; 
 int nvlist_get_number (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,size_t) ; 

int
ixl_if_iov_vf_add(if_ctx_t ctx, uint16_t vfnum, const nvlist_t *params)
{
	struct ixl_pf *pf = iflib_get_softc(ctx);
	device_t dev = pf->dev;
	char sysctl_name[QUEUE_NAME_LEN];
	struct ixl_vf *vf;
	const void *mac;
	size_t size;
	int error;
	int vf_num_queues;

	vf = &pf->vfs[vfnum];
	vf->vf_num = vfnum;
	vf->vsi.back = pf;
	vf->vf_flags = VF_FLAG_ENABLED;
	SLIST_INIT(&vf->vsi.ftl);

	/* Reserve queue allocation from PF */
	vf_num_queues = nvlist_get_number(params, "num-queues");
	error = ixl_vf_reserve_queues(pf, vf, vf_num_queues);
	if (error != 0)
		goto out;

	error = ixl_vf_setup_vsi(pf, vf);
	if (error != 0)
		goto out;

	if (nvlist_exists_binary(params, "mac-addr")) {
		mac = nvlist_get_binary(params, "mac-addr", &size);
		bcopy(mac, vf->mac, ETHER_ADDR_LEN);

		if (nvlist_get_bool(params, "allow-set-mac"))
			vf->vf_flags |= VF_FLAG_SET_MAC_CAP;
	} else
		/*
		 * If the administrator has not specified a MAC address then
		 * we must allow the VF to choose one.
		 */
		vf->vf_flags |= VF_FLAG_SET_MAC_CAP;

	if (nvlist_get_bool(params, "mac-anti-spoof"))
		vf->vf_flags |= VF_FLAG_MAC_ANTI_SPOOF;

	if (nvlist_get_bool(params, "allow-promisc"))
		vf->vf_flags |= VF_FLAG_PROMISC_CAP;

	vf->vf_flags |= VF_FLAG_VLAN_CAP;

	/* VF needs to be reset before it can be used */
	ixl_reset_vf(pf, vf);
out:
	if (error == 0) {
		snprintf(sysctl_name, sizeof(sysctl_name), "vf%d", vfnum);
		ixl_add_vsi_sysctls(dev, &vf->vsi, &vf->ctx, sysctl_name);
	}

	return (error);
}