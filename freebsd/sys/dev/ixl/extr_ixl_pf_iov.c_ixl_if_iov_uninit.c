#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ixl_vsi {struct ifnet* ifp; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_allocated; } ;
struct TYPE_4__ {scalar_t__ seid; } ;
struct ixl_vf {int /*<<< orphan*/  ctx; TYPE_1__ qtag; TYPE_2__ vsi; } ;
struct i40e_hw {int dummy; } ;
struct ixl_pf {int num_vfs; scalar_t__ veb_seid; struct ixl_vf* vfs; scalar_t__ enable_vf_loopback; int /*<<< orphan*/  qmgr; struct ixl_vsi vsi; struct i40e_hw hw; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_IXL ; 
 int /*<<< orphan*/  free (struct ixl_vf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_aq_delete_element (struct i40e_hw*,scalar_t__,int /*<<< orphan*/ *) ; 
 struct ixl_pf* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_config_pf_vsi_loopback (struct ixl_pf*,int) ; 
 int /*<<< orphan*/  ixl_dbg_iov (struct ixl_pf*,char*,int,...) ; 
 int /*<<< orphan*/  ixl_free_mac_filters (TYPE_2__*) ; 
 int /*<<< orphan*/  ixl_pf_qmgr_get_num_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixl_pf_qmgr_release (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 

void
ixl_if_iov_uninit(if_ctx_t ctx)
{
	struct ixl_pf *pf = iflib_get_softc(ctx);
	struct i40e_hw *hw;
	struct ixl_vsi *vsi;
	struct ifnet *ifp;
	struct ixl_vf *vfs;
	int i, num_vfs;

	hw = &pf->hw;
	vsi = &pf->vsi;
	ifp = vsi->ifp;

	for (i = 0; i < pf->num_vfs; i++) {
		if (pf->vfs[i].vsi.seid != 0)
			i40e_aq_delete_element(hw, pf->vfs[i].vsi.seid, NULL);
		ixl_pf_qmgr_release(&pf->qmgr, &pf->vfs[i].qtag);
		ixl_free_mac_filters(&pf->vfs[i].vsi);
		ixl_dbg_iov(pf, "VF %d: %d released\n",
		    i, pf->vfs[i].qtag.num_allocated);
		ixl_dbg_iov(pf, "Unallocated total: %d\n", ixl_pf_qmgr_get_num_free(&pf->qmgr));
	}

	if (pf->veb_seid != 0) {
		i40e_aq_delete_element(hw, pf->veb_seid, NULL);
		pf->veb_seid = 0;
	}
	/* Reset PF VSI loopback mode */
	if (pf->enable_vf_loopback)
		ixl_config_pf_vsi_loopback(pf, false);

	vfs = pf->vfs;
	num_vfs = pf->num_vfs;

	pf->vfs = NULL;
	pf->num_vfs = 0;

	/* sysctl_ctx_free might sleep, but this func is called w/ an sx lock */
	for (i = 0; i < num_vfs; i++)
		sysctl_ctx_free(&vfs[i].ctx);
	free(vfs, M_IXL);
}