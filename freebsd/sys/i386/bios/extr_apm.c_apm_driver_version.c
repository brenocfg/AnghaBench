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
struct apm_softc {TYPE_2__ bios; } ;

/* Variables and functions */
 int APM_BIOS ; 
 int APM_DRVVERSION ; 
 scalar_t__ apm_bioscall () ; 
 struct apm_softc apm_softc ; 

__attribute__((used)) static int
apm_driver_version(int version)
{
	struct apm_softc *sc = &apm_softc;

	sc->bios.r.eax = (APM_BIOS << 8) | APM_DRVVERSION;
	sc->bios.r.ebx  = 0x0;
	sc->bios.r.ecx  = version;
	sc->bios.r.edx = 0;

	if (apm_bioscall() == 0 && sc->bios.r.eax == version)
		return (0);

	/* Some old BIOSes don't return the connection version in %ax. */
	if (sc->bios.r.eax == ((APM_BIOS << 8) | APM_DRVVERSION))
		return (0);

	return (1);
}