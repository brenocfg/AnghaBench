#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int rx_mask; } ;
struct bnxt_softc {TYPE_4__ vnic_info; } ;
typedef  TYPE_1__* if_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
struct TYPE_5__ {int if_flags; } ;

/* Variables and functions */
 scalar_t__ BNXT_MAX_MC_ADDRS ; 
 int HWRM_CFA_L2_SET_RX_MASK_INPUT_MASK_ALL_MCAST ; 
 int HWRM_CFA_L2_SET_RX_MASK_INPUT_MASK_ANYVLAN_NONVLAN ; 
 int HWRM_CFA_L2_SET_RX_MASK_INPUT_MASK_PROMISCUOUS ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int bnxt_hwrm_cfa_l2_set_rx_mask (struct bnxt_softc*,TYPE_4__*) ; 
 scalar_t__ if_llmaddr_count (TYPE_1__*) ; 
 TYPE_1__* iflib_get_ifp (int /*<<< orphan*/ ) ; 
 struct bnxt_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bnxt_promisc_set(if_ctx_t ctx, int flags)
{
	struct bnxt_softc *softc = iflib_get_softc(ctx);
	if_t ifp = iflib_get_ifp(ctx);
	int rc;

	if (ifp->if_flags & IFF_ALLMULTI ||
	    if_llmaddr_count(ifp) > BNXT_MAX_MC_ADDRS)
		softc->vnic_info.rx_mask |=
		    HWRM_CFA_L2_SET_RX_MASK_INPUT_MASK_ALL_MCAST;
	else
		softc->vnic_info.rx_mask &=
		    ~HWRM_CFA_L2_SET_RX_MASK_INPUT_MASK_ALL_MCAST;

	if (ifp->if_flags & IFF_PROMISC)
		softc->vnic_info.rx_mask |=
		    HWRM_CFA_L2_SET_RX_MASK_INPUT_MASK_PROMISCUOUS |
		    HWRM_CFA_L2_SET_RX_MASK_INPUT_MASK_ANYVLAN_NONVLAN;
	else
		softc->vnic_info.rx_mask &=
		    ~(HWRM_CFA_L2_SET_RX_MASK_INPUT_MASK_PROMISCUOUS |
		    HWRM_CFA_L2_SET_RX_MASK_INPUT_MASK_ANYVLAN_NONVLAN);

	rc = bnxt_hwrm_cfa_l2_set_rx_mask(softc, &softc->vnic_info);

	return rc;
}