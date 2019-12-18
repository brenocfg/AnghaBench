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
typedef  int /*<<< orphan*/  strbuf ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ ocd_data; } ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int ET_TMR_NUM ; 
 int TC_TMR_NUM ; 
 int /*<<< orphan*/  compat_data ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_status_okay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int ti_hwmods_get_unit (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
am335x_dmtimer_probe(device_t dev)
{
	char strbuf[32];
	int tmr_num;

	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	if (ofw_bus_search_compatible(dev, compat_data)->ocd_data == 0)
		return (ENXIO);

	/*
	 * Get the hardware unit number (the N from ti,hwmods="timerN").
	 * If this isn't the hardware unit we're going to use for either the
	 * eventtimer or the timecounter, no point in instantiating the device.
	 */
	tmr_num = ti_hwmods_get_unit(dev, "timer");
	if (tmr_num != ET_TMR_NUM && tmr_num != TC_TMR_NUM)
		return (ENXIO);

	snprintf(strbuf, sizeof(strbuf), "AM335x DMTimer%d", tmr_num);
	device_set_desc_copy(dev, strbuf);

	return(BUS_PROBE_DEFAULT);
}