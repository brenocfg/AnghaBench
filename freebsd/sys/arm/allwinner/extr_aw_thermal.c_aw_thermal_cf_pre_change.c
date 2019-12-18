#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ freq; } ;
struct cf_level {TYPE_1__ total_set; } ;
struct aw_thermal_softc {scalar_t__ throttle; scalar_t__ min_freq; } ;

/* Variables and functions */
 int ENXIO ; 
 int aw_thermal_getalarm (struct aw_thermal_softc*,int /*<<< orphan*/ ) ; 
 int aw_thermal_gettemp (struct aw_thermal_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aw_thermal_throttle (struct aw_thermal_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ aw_thermal_throttle_enable ; 

__attribute__((used)) static void
aw_thermal_cf_pre_change(void *arg, const struct cf_level *level, int *status)
{
	struct aw_thermal_softc *sc;
	int temp_cur, temp_alarm;

	sc = arg;

	if (aw_thermal_throttle_enable == 0 || sc->throttle == 0 ||
	    level->total_set.freq == sc->min_freq)
		return;

	temp_cur = aw_thermal_gettemp(sc, 0);
	temp_alarm = aw_thermal_getalarm(sc, 0);

	if (temp_cur < temp_alarm)
		aw_thermal_throttle(sc, 0);
	else
		*status = ENXIO;
}