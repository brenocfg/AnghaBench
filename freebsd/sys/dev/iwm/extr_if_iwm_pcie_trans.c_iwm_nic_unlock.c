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
struct iwm_softc {scalar_t__ cmd_hold_nic_awake; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_CLRBITS (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWM_CSR_GP_CNTRL ; 
 int /*<<< orphan*/  IWM_CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ ; 

void
iwm_nic_unlock(struct iwm_softc *sc)
{
	if (sc->cmd_hold_nic_awake)
		return;

	IWM_CLRBITS(sc, IWM_CSR_GP_CNTRL,
	    IWM_CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);
}