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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ ZIP_MAX_CORES ; 

__attribute__((used)) static const char *get_feature_option(u8 zip_cores, int core_freq)
{
	if (zip_cores == 0)
		return "";
	else if (zip_cores < ZIP_MAX_CORES)
		return "-C15";

	if (core_freq >= 850)
		return "-C45";
	else if (core_freq >= 750)
		return "-C35";
	else if (core_freq >= 550)
		return "-C25";

	return "";
}