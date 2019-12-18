#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int eax; scalar_t__ ebx; int ecx; int edx; } ;
struct TYPE_6__ {TYPE_1__ r; } ;
struct apm_softc {TYPE_2__ bios; } ;
typedef  TYPE_3__* apm_pwstatus_t ;
struct TYPE_7__ {scalar_t__ ap_device; int ap_acline; int ap_batt_stat; int ap_batt_flag; int ap_batt_life; int ap_batt_time; } ;

/* Variables and functions */
 int APM_BIOS ; 
 int APM_GETPWSTATUS ; 
 scalar_t__ PMDV_ALLDEV ; 
 scalar_t__ PMDV_BATT0 ; 
 scalar_t__ PMDV_BATT_ALL ; 
 int __bswap16 (int) ; 
 scalar_t__ apm_bioscall () ; 
 struct apm_softc apm_softc ; 
 scalar_t__ apm_swab_batt_minutes ; 

__attribute__((used)) static int
apm_get_pwstatus(apm_pwstatus_t app)
{
	struct apm_softc *sc = &apm_softc;

	if (app->ap_device != PMDV_ALLDEV &&
	    (app->ap_device < PMDV_BATT0 || app->ap_device > PMDV_BATT_ALL))
		return 1;

	sc->bios.r.eax = (APM_BIOS << 8) | APM_GETPWSTATUS;
	sc->bios.r.ebx = app->ap_device;
	sc->bios.r.ecx = 0;
	sc->bios.r.edx = 0xffff;	/* default to unknown battery time */

	if (apm_bioscall())
		return 1;

	app->ap_acline    = (sc->bios.r.ebx >> 8) & 0xff;
	app->ap_batt_stat = sc->bios.r.ebx & 0xff;
	app->ap_batt_flag = (sc->bios.r.ecx >> 8) & 0xff;
	app->ap_batt_life = sc->bios.r.ecx & 0xff;
	sc->bios.r.edx &= 0xffff;
	if (apm_swab_batt_minutes)
		sc->bios.r.edx = __bswap16(sc->bios.r.edx) | 0x8000;
	if (sc->bios.r.edx == 0xffff)	/* Time is unknown */
		app->ap_batt_time = -1;
	else if (sc->bios.r.edx & 0x8000)	/* Time is in minutes */
		app->ap_batt_time = (sc->bios.r.edx & 0x7fff) * 60;
	else				/* Time is in seconds */
		app->ap_batt_time = sc->bios.r.edx;

	return 0;
}