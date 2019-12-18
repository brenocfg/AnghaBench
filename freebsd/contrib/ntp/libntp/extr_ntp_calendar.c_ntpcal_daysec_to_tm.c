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
struct tm {void* tm_sec; void* tm_min; void* tm_hour; } ;
typedef  void* int32_t ;

/* Variables and functions */
 void* priv_timesplit (void**,void*) ; 

int32_t
ntpcal_daysec_to_tm(
	struct tm *utm,
	int32_t	   sec
	)
{
	int32_t days;
	int32_t ts[3];

	days = priv_timesplit(ts, sec);
	utm->tm_hour = ts[0];
	utm->tm_min  = ts[1];
	utm->tm_sec  = ts[2];

	return days;
}