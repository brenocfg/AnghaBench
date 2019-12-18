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
typedef  void* uint8_t ;
struct calendar {void* second; void* minute; void* hour; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  priv_timesplit (int*,int /*<<< orphan*/ ) ; 

int32_t
ntpcal_daysec_to_date(
	struct calendar *jd,
	int32_t		sec
	)
{
	int32_t days;
	int   ts[3];

	days = priv_timesplit(ts, sec);
	jd->hour   = (uint8_t)ts[0];
	jd->minute = (uint8_t)ts[1];
	jd->second = (uint8_t)ts[2];

	return days;
}