#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ixl_vsi {int /*<<< orphan*/  seid; struct i40e_hw* hw; struct ifnet* ifp; } ;
struct ifnet {int dummy; } ;
struct i40e_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOCTL_DEBUGOUT (char*) ; 
 int IXL_FILTER_ADD ; 
 int IXL_FILTER_MC ; 
 int IXL_FILTER_USED ; 
 int MAX_MULTICAST_ADDR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  i40e_aq_set_vsi_multicast_promiscuous (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,struct ixl_vsi*) ; 
 int if_llmaddr_count (struct ifnet*) ; 
 int /*<<< orphan*/  ixl_add_hw_filters (struct ixl_vsi*,int,int) ; 
 int /*<<< orphan*/  ixl_add_maddr ; 
 int /*<<< orphan*/  ixl_del_hw_filters (struct ixl_vsi*,int) ; 

void
ixl_add_multi(struct ixl_vsi *vsi)
{
	struct ifnet		*ifp = vsi->ifp;
	struct i40e_hw		*hw = vsi->hw;
	int			mcnt = 0, flags;

	IOCTL_DEBUGOUT("ixl_add_multi: begin");

	/*
	** First just get a count, to decide if we
	** we simply use multicast promiscuous.
	*/
	mcnt = if_llmaddr_count(ifp);
	if (__predict_false(mcnt >= MAX_MULTICAST_ADDR)) {
		/* delete existing MC filters */
		ixl_del_hw_filters(vsi, mcnt);
		i40e_aq_set_vsi_multicast_promiscuous(hw,
		    vsi->seid, TRUE, NULL);
		return;
	}

	mcnt = if_foreach_llmaddr(ifp, ixl_add_maddr, vsi);
	if (mcnt > 0) {
		flags = (IXL_FILTER_ADD | IXL_FILTER_USED | IXL_FILTER_MC);
		ixl_add_hw_filters(vsi, flags, mcnt);
	}

	IOCTL_DEBUGOUT("ixl_add_multi: end");
}