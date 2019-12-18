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
struct apm_softc {scalar_t__ initialized; int /*<<< orphan*/  standby_countdown; int /*<<< orphan*/  standbys; int /*<<< orphan*/  suspend_countdown; int /*<<< orphan*/  suspends; } ;

/* Variables and functions */
#define  PMST_STANDBY 129 
#define  PMST_SUSPEND 128 
 int /*<<< orphan*/  apm_lastreq_notify () ; 
 int /*<<< orphan*/  apm_op_inprog ; 
 struct apm_softc apm_softc ; 
 int /*<<< orphan*/  apm_standby_delay ; 
 int /*<<< orphan*/  apm_suspend_delay ; 
 int /*<<< orphan*/  printf (char*,int) ; 

void
apm_suspend(int state)
{
	struct apm_softc *sc = &apm_softc;

	if (sc == NULL || sc->initialized == 0)
		return;

	switch (state) {
	case PMST_SUSPEND:
		if (sc->suspends)
			return;
		sc->suspends++;
		sc->suspend_countdown = apm_suspend_delay;
		break;
	case PMST_STANDBY:
		if (sc->standbys)
			return;
		sc->standbys++;
		sc->standby_countdown = apm_standby_delay;
		break;
	default:
		printf("apm_suspend: Unknown Suspend state 0x%x\n", state);
		return;
	}

	apm_op_inprog++;
	apm_lastreq_notify();
}