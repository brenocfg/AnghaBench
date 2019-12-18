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
struct TYPE_3__ {int eax; int ebx; int ecx; scalar_t__ edx; } ;
struct TYPE_4__ {TYPE_1__ r; } ;
struct apm_softc {scalar_t__ intversion; TYPE_2__ bios; } ;

/* Variables and functions */
 int APM_BIOS ; 
 int APM_ENABLEDISABLEPM ; 
 scalar_t__ INTVERSION (int,int) ; 
 int PMDV_ALLDEV ; 
 int apm_bioscall () ; 
 struct apm_softc apm_softc ; 

__attribute__((used)) static int
apm_enable_disable_pm(int enable)
{
	struct apm_softc *sc = &apm_softc;

	sc->bios.r.eax = (APM_BIOS << 8) | APM_ENABLEDISABLEPM;

	if (sc->intversion >= INTVERSION(1, 1))
		sc->bios.r.ebx  = PMDV_ALLDEV;
	else
		sc->bios.r.ebx  = 0xffff;	/* APM version 1.0 only */
	sc->bios.r.ecx  = enable;
	sc->bios.r.edx = 0;
	return (apm_bioscall());
}