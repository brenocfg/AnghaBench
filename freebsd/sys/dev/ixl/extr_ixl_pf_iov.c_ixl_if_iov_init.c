#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct ixl_vsi {int /*<<< orphan*/  seid; int /*<<< orphan*/  uplink_seid; } ;
struct ixl_vf {int dummy; } ;
struct TYPE_4__ {int asq_last_status; } ;
struct i40e_hw {TYPE_1__ aq; } ;
struct ixl_pf {int num_vfs; TYPE_2__* vfs; scalar_t__ enable_vf_loopback; int /*<<< orphan*/  veb_seid; struct ixl_vsi vsi; struct i40e_hw hw; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
 int I40E_SUCCESS ; 
 int /*<<< orphan*/  M_IXL ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int i40e_aq_add_veb (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_aq_str (struct i40e_hw*,int) ; 
 int /*<<< orphan*/  i40e_stat_str (struct i40e_hw*,int) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct ixl_pf* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_config_pf_vsi_loopback (struct ixl_pf*,int) ; 
 int /*<<< orphan*/  ixl_del_default_hw_filters (struct ixl_vsi*) ; 
 int /*<<< orphan*/  ixl_reconfigure_filters (struct ixl_vsi*) ; 
 TYPE_2__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sysctl_ctx_init (int /*<<< orphan*/ *) ; 

int
ixl_if_iov_init(if_ctx_t ctx, uint16_t num_vfs, const nvlist_t *params)
{
	struct ixl_pf *pf = iflib_get_softc(ctx);
	device_t dev = iflib_get_dev(ctx);
	struct i40e_hw *hw;
	struct ixl_vsi *pf_vsi;
	enum i40e_status_code ret;
	int i, error;

	hw = &pf->hw;
	pf_vsi = &pf->vsi;

	pf->vfs = malloc(sizeof(struct ixl_vf) * num_vfs, M_IXL, M_NOWAIT |
	    M_ZERO);
	if (pf->vfs == NULL) {
		error = ENOMEM;
		goto fail;
	}

	for (i = 0; i < num_vfs; i++)
		sysctl_ctx_init(&pf->vfs[i].ctx);

	/*
	 * Add the VEB and ...
	 * - do nothing: VEPA mode
	 * - enable loopback mode on connected VSIs: VEB mode
	 */
	ret = i40e_aq_add_veb(hw, pf_vsi->uplink_seid, pf_vsi->seid,
	    1, FALSE, &pf->veb_seid, FALSE, NULL);
	if (ret != I40E_SUCCESS) {
		error = hw->aq.asq_last_status;
		device_printf(dev, "i40e_aq_add_veb failed; status %s error %s",
		    i40e_stat_str(hw, ret), i40e_aq_str(hw, error));
		goto fail;
	}
	if (pf->enable_vf_loopback)
		ixl_config_pf_vsi_loopback(pf, true);

	/*
	 * Adding a VEB brings back the default MAC filter(s). Remove them,
	 * and let the driver add the proper filters back.
	 */
	ixl_del_default_hw_filters(pf_vsi);
	ixl_reconfigure_filters(pf_vsi);

	pf->num_vfs = num_vfs;
	return (0);

fail:
	free(pf->vfs, M_IXL);
	pf->vfs = NULL;
	return (error);
}