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
struct ixl_vsi {int /*<<< orphan*/  media; TYPE_1__* shared; int /*<<< orphan*/  ctx; } ;
struct ifnet {scalar_t__ if_mtu; } ;
struct iavf_sc {struct ixl_vsi vsi; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ isc_max_frame_size; } ;

/* Variables and functions */
 scalar_t__ ETHER_CRC_LEN ; 
 scalar_t__ ETHER_HDR_LEN ; 
 scalar_t__ ETHER_VLAN_ENCAP_LEN ; 
 int IFM_AUTO ; 
 int IFM_ETHER ; 
 int /*<<< orphan*/  IF_Gbps (int) ; 
 int /*<<< orphan*/  INIT_DBG_DEV (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  if_initbaudrate (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setbaudrate (struct ifnet*,int /*<<< orphan*/ ) ; 
 struct ifnet* iflib_get_ifp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_add (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_set (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
iavf_setup_interface(device_t dev, struct iavf_sc *sc)
{
	struct ixl_vsi *vsi = &sc->vsi;
	if_ctx_t ctx = vsi->ctx;
	struct ifnet *ifp = iflib_get_ifp(ctx);

	INIT_DBG_DEV(dev, "begin");

	vsi->shared->isc_max_frame_size =
	    ifp->if_mtu + ETHER_HDR_LEN + ETHER_CRC_LEN
	    + ETHER_VLAN_ENCAP_LEN;
#if __FreeBSD_version >= 1100000
	if_setbaudrate(ifp, IF_Gbps(40));
#else
	if_initbaudrate(ifp, IF_Gbps(40));
#endif

	ifmedia_add(vsi->media, IFM_ETHER | IFM_AUTO, 0, NULL);
	ifmedia_set(vsi->media, IFM_ETHER | IFM_AUTO);
}