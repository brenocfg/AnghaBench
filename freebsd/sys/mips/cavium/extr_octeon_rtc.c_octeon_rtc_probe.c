#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ cvmx_rtc_options_t ;

/* Variables and functions */
 int BUS_PROBE_NOWILDCARD ; 
 int ENXIO ; 
 scalar_t__ cvmx_rtc_supported () ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
octeon_rtc_probe(device_t dev)
{
	cvmx_rtc_options_t supported;

	if (device_get_unit(dev) != 0)
		return (ENXIO);

	supported = cvmx_rtc_supported();
	if (supported == 0)
		return (ENXIO);

	device_set_desc(dev, "Cavium Octeon Realtime Clock");
	return (BUS_PROBE_NOWILDCARD);
}