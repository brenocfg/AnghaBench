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
typedef  int int32_t ;

/* Variables and functions */
 int DAYSPERYEAR ; 
 int ntpcal_leapyears_in_years (int) ; 

int32_t
ntpcal_days_in_years(
	int32_t years
	)
{
	return years * DAYSPERYEAR + ntpcal_leapyears_in_years(years);
}