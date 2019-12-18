#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
struct TYPE_3__ {int minutes; int hours; int days; int weeks; int months; int years; scalar_t__ seconds; } ;
typedef  TYPE_1__ ldns_duration_type ;

/* Variables and functions */

time_t
ldns_duration2time(const ldns_duration_type* duration)
{
    time_t period = 0;

    if (duration) {
        period += (duration->seconds);
        period += (duration->minutes)*60;
        period += (duration->hours)*3600;
        period += (duration->days)*86400;
        period += (duration->weeks)*86400*7;
        period += (duration->months)*86400*31;
        period += (duration->years)*86400*365;

        /* [TODO] calculate correct number of days in this month/year */
	/*
        if (duration->months || duration->years) {
        }
	*/
    }
    return period;
}