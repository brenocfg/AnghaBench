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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_hour; int tm_min; scalar_t__ tm_yday; scalar_t__ tm_year; } ;

/* Variables and functions */
 int /*<<< orphan*/  gmtime_r (int /*<<< orphan*/ *,struct tm*) ; 

__attribute__((used)) static int calc_gmt_offset(time_t t, struct tm *local)
{
    struct tm gmt;
    int delta;

    gmtime_r(&t, &gmt);
    delta = (local->tm_hour - gmt.tm_hour) * 60 + (local->tm_min - gmt.tm_min);

    if (local->tm_yday != gmt.tm_yday) {
        int day_offset;
        if (local->tm_year == gmt.tm_year)
            day_offset = local->tm_yday - gmt.tm_yday;
        else
            day_offset = local->tm_year - gmt.tm_year;
        delta += day_offset * 24 * 60;
    }
    return delta;
}