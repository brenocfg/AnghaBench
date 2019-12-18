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
struct ixl_vsi {int /*<<< orphan*/  seid; struct i40e_hw* hw; } ;
struct ixl_pf {struct ixl_vsi vsi; } ;
struct ifnet {int dummy; } ;
struct i40e_hw {int dummy; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int FALSE ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 scalar_t__ MAX_MULTICAST_ADDR ; 
 int TRUE ; 
 int i40e_aq_set_vsi_multicast_promiscuous (struct i40e_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int i40e_aq_set_vsi_unicast_promiscuous (struct i40e_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ if_llmaddr_count (struct ifnet*) ; 
 struct ifnet* iflib_get_ifp (int /*<<< orphan*/ ) ; 
 struct ixl_pf* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ixl_if_promisc_set(if_ctx_t ctx, int flags)
{
	struct ixl_pf *pf = iflib_get_softc(ctx);
	struct ixl_vsi *vsi = &pf->vsi;
	struct ifnet	*ifp = iflib_get_ifp(ctx);
	struct i40e_hw	*hw = vsi->hw;
	int		err;
	bool		uni = FALSE, multi = FALSE;

	if (flags & IFF_PROMISC)
		uni = multi = TRUE;
	else if (flags & IFF_ALLMULTI || if_llmaddr_count(ifp) >=
	    MAX_MULTICAST_ADDR)
		multi = TRUE;

	err = i40e_aq_set_vsi_unicast_promiscuous(hw,
	    vsi->seid, uni, NULL, true);
	if (err)
		return (err);
	err = i40e_aq_set_vsi_multicast_promiscuous(hw,
	    vsi->seid, multi, NULL);
	return (err);
}