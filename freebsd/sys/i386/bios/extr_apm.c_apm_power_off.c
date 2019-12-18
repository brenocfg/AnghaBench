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
struct TYPE_4__ {int eax; scalar_t__ edx; int /*<<< orphan*/  ecx; int /*<<< orphan*/  ebx; } ;
struct TYPE_3__ {TYPE_2__ r; } ;
struct apm_softc {TYPE_1__ bios; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int APM_BIOS ; 
 int APM_SETPWSTATE ; 
 int /*<<< orphan*/  PMDV_ALLDEV ; 
 int /*<<< orphan*/  PMST_OFF ; 
 int RB_POWEROFF ; 
 int /*<<< orphan*/  apm_bioscall () ; 
 struct apm_softc apm_softc ; 

__attribute__((used)) static void
apm_power_off(void *junk, int howto)
{
	struct apm_softc *sc = &apm_softc;

	/* Not halting powering off, or not active */
	if (!(howto & RB_POWEROFF) || !apm_softc.active)
		return;
	sc->bios.r.eax = (APM_BIOS << 8) | APM_SETPWSTATE;
	sc->bios.r.ebx = PMDV_ALLDEV;
	sc->bios.r.ecx = PMST_OFF;
	sc->bios.r.edx = 0;
	(void) apm_bioscall();
}