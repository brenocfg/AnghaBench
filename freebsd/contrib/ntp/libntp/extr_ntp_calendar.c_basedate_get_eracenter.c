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
typedef  int time_t ;

/* Variables and functions */
 scalar_t__ NTP_TO_UNIX_DAYS ; 
 int SECSPERDAY ; 
 int UINT32_C (int) ; 
 scalar_t__ s_baseday ; 

time_t
basedate_get_eracenter(void)
{
	time_t retv;
	retv  = (time_t)(s_baseday - NTP_TO_UNIX_DAYS);
	retv *= SECSPERDAY;
	retv += (UINT32_C(1) << 31);
	return retv;
}