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
struct iwm_vap {int /*<<< orphan*/  phy_ctxt; int /*<<< orphan*/  iv_vap; } ;
struct iwm_softc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int iwm_mvm_binding_update (struct iwm_softc*,struct iwm_vap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iwm_mvm_sf_update (struct iwm_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
iwm_mvm_binding_add_vif(struct iwm_softc *sc, struct iwm_vap *ivp)
{
	if (!ivp->phy_ctxt)
		return EINVAL;

	/*
	 * Update SF - Disable if needed. if this fails, SF might still be on
	 * while many macs are bound, which is forbidden - so fail the binding.
	 */
	if (iwm_mvm_sf_update(sc, &ivp->iv_vap, FALSE))
		return EINVAL;

	return iwm_mvm_binding_update(sc, ivp, ivp->phy_ctxt, TRUE);
}