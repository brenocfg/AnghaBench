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
struct TYPE_4__ {int eax; scalar_t__ ebx; scalar_t__ ecx; scalar_t__ edx; } ;
struct TYPE_3__ {TYPE_2__ r; } ;
struct apm_softc {scalar_t__ always_halt_cpu; scalar_t__ active; TYPE_1__ bios; } ;

/* Variables and functions */
 int APM_BIOS ; 
 int APM_CPUIDLE ; 
 int /*<<< orphan*/  apm_bioscall () ; 
 struct apm_softc apm_softc ; 
 int /*<<< orphan*/  halt () ; 

void
apm_cpu_idle(void)
{
	struct apm_softc *sc = &apm_softc;

	if (sc->active) {

		sc->bios.r.eax = (APM_BIOS <<8) | APM_CPUIDLE;
		sc->bios.r.edx = sc->bios.r.ecx = sc->bios.r.ebx = 0;
		(void) apm_bioscall();
	}
	/*
	 * Some APM implementation halts CPU in BIOS, whenever
	 * "CPU-idle" function are invoked, but swtch() of
	 * FreeBSD halts CPU, therefore, CPU is halted twice
	 * in the sched loop. It makes the interrupt latency
	 * terribly long and be able to cause a serious problem
	 * in interrupt processing. We prevent it by removing
	 * "hlt" operation from swtch() and managed it under
	 * APM driver.
	 */
	if (!sc->active || sc->always_halt_cpu)
		halt();	/* wait for interrupt */
}