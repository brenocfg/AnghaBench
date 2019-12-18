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
struct TYPE_3__ {int eax; scalar_t__ edx; int /*<<< orphan*/  ecx; int /*<<< orphan*/  ebx; } ;
struct TYPE_4__ {TYPE_1__ r; } ;
struct apm_softc {TYPE_2__ bios; } ;

/* Variables and functions */
 int APM_BIOS ; 
 int /*<<< orphan*/  APM_DPRINT (char*) ; 
 int APM_SETPWSTATE ; 
 int /*<<< orphan*/  PMDV_ALLDEV ; 
 int /*<<< orphan*/  PMST_LASTREQREJECT ; 
 scalar_t__ apm_bioscall () ; 
 scalar_t__ apm_op_inprog ; 
 struct apm_softc apm_softc ; 

__attribute__((used)) static int
apm_lastreq_rejected(void)
{
	struct apm_softc *sc = &apm_softc;

	if (apm_op_inprog == 0) {
		return 1;	/* no operation in progress */
	}

	sc->bios.r.eax = (APM_BIOS << 8) | APM_SETPWSTATE;
	sc->bios.r.ebx = PMDV_ALLDEV;
	sc->bios.r.ecx = PMST_LASTREQREJECT;
	sc->bios.r.edx = 0;

	if (apm_bioscall()) {
		APM_DPRINT("apm_lastreq_rejected: failed\n");
		return 1;
	}
	apm_op_inprog = 0;
	return 0;
}