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
typedef  int cvmx_rtc_options_t ;

/* Variables and functions */
 int CVMX_RTC_READ ; 
 int ENXIO ; 
 int /*<<< orphan*/  clock_register (int /*<<< orphan*/ ,int) ; 
 int cvmx_rtc_supported () ; 

__attribute__((used)) static int
octeon_rtc_attach(device_t dev)
{
	cvmx_rtc_options_t supported;

	supported = cvmx_rtc_supported();
	if ((supported & CVMX_RTC_READ) == 0)
		return (ENXIO);

	clock_register(dev, 1000000);
	return (0);
}