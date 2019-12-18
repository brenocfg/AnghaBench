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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__* psci_fnids; } ;

/* Variables and functions */
 size_t PSCI_FN_SYSTEM_OFF ; 
 size_t PSCI_FN_SYSTEM_RESET ; 
 int RB_HALT ; 
 int RB_POWEROFF ; 
 int /*<<< orphan*/  psci_call (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* psci_softc ; 

__attribute__((used)) static void
psci_shutdown(void *xsc, int howto)
{
	uint32_t fn = 0;

	if (psci_softc == NULL)
		return;

	/* PSCI system_off and system_reset werent't supported in v0.1. */
	if ((howto & RB_POWEROFF) != 0)
		fn = psci_softc->psci_fnids[PSCI_FN_SYSTEM_OFF];
	else if ((howto & RB_HALT) == 0)
		fn = psci_softc->psci_fnids[PSCI_FN_SYSTEM_RESET];

	if (fn)
		psci_call(fn, 0, 0, 0);

	/* System reset and off do not return. */
}