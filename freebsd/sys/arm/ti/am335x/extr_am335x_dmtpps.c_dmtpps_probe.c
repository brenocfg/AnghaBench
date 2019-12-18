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
 int /*<<< orphan*/  compat_data ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 int dmtpps_find_tmr_num () ; 
 int dmtpps_tmr_num ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_status_okay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int ti_hwmods_get_unit (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
dmtpps_probe(device_t dev)
{
	char strbuf[64];
	int tmr_num;

	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	if (ofw_bus_search_compatible(dev, compat_data)->ocd_data == 0)
		return (ENXIO);

	/*
	 * If we haven't chosen which hardware timer to use yet, go do that now.
	 * We need to know that to decide whether to return success for this
	 * hardware timer instance or not.
	 */
	if (dmtpps_tmr_num == 0)
		dmtpps_tmr_num = dmtpps_find_tmr_num();

	/*
	 * Figure out which hardware timer is being probed and see if it matches
	 * the configured timer number determined earlier.
	 */
	tmr_num = ti_hwmods_get_unit(dev, "timer");
	if (dmtpps_tmr_num != tmr_num)
		return (ENXIO);

	snprintf(strbuf, sizeof(strbuf), "AM335x PPS-Capture DMTimer%d",
	    tmr_num);
	device_set_desc_copy(dev, strbuf);

	return(BUS_PROBE_DEFAULT);
}