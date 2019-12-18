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
struct TYPE_3__ {int eax; int ecx; scalar_t__ edx; int /*<<< orphan*/  ebx; } ;
struct TYPE_4__ {TYPE_1__ r; } ;
struct apm_softc {TYPE_2__ bios; } ;

/* Variables and functions */
 int APM_BIOS ; 
 int APM_SETPWSTATE ; 
 int /*<<< orphan*/  PMDV_ALLDEV ; 
 scalar_t__ apm_bioscall () ; 
 struct apm_softc apm_softc ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
apm_suspend_system(int state)
{
	struct apm_softc *sc = &apm_softc;

	sc->bios.r.eax = (APM_BIOS << 8) | APM_SETPWSTATE;
	sc->bios.r.ebx = PMDV_ALLDEV;
	sc->bios.r.ecx = state;
	sc->bios.r.edx = 0;

	if (apm_bioscall()) {
 		printf("Entire system suspend failure: errcode = %d\n",
		       0xff & (sc->bios.r.eax >> 8));
 		return 1;
 	}

 	return 0;
}