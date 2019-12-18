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
struct TYPE_3__ {int eax; scalar_t__ ebx; scalar_t__ ecx; scalar_t__ edx; } ;
struct TYPE_4__ {TYPE_1__ r; } ;
struct apm_softc {TYPE_2__ bios; scalar_t__ active; scalar_t__ slow_idle_cpu; } ;

/* Variables and functions */
 int APM_BIOS ; 
 int APM_CPUBUSY ; 
 int /*<<< orphan*/  apm_bioscall () ; 
 struct apm_softc apm_softc ; 

void
apm_cpu_busy(void)
{
	struct apm_softc *sc = &apm_softc;

	/*
	 * The APM specification says this is only necessary if your BIOS
	 * slows down the processor in the idle task, otherwise it's not
	 * necessary.
	 */
	if (sc->slow_idle_cpu && sc->active) {

		sc->bios.r.eax = (APM_BIOS <<8) | APM_CPUBUSY;
		sc->bios.r.edx = sc->bios.r.ecx = sc->bios.r.ebx = 0;
		apm_bioscall();
	}
}