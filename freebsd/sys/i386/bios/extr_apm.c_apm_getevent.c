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
typedef  int u_int ;
struct TYPE_4__ {int eax; int ebx; scalar_t__ edx; scalar_t__ ecx; } ;
struct TYPE_3__ {TYPE_2__ r; } ;
struct apm_softc {TYPE_1__ bios; } ;

/* Variables and functions */
 int APM_BIOS ; 
 int APM_GETPMEVENT ; 
 int PMEV_NOEVENT ; 
 scalar_t__ apm_bioscall () ; 
 struct apm_softc apm_softc ; 

__attribute__((used)) static u_int
apm_getevent(void)
{
	struct apm_softc *sc = &apm_softc;

	sc->bios.r.eax = (APM_BIOS << 8) | APM_GETPMEVENT;

	sc->bios.r.ebx = 0;
	sc->bios.r.ecx = 0;
	sc->bios.r.edx = 0;
	if (apm_bioscall())
		return (PMEV_NOEVENT);
	return (sc->bios.r.ebx & 0xffff);
}