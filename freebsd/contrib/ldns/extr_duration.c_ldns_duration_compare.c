#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ years; scalar_t__ months; scalar_t__ weeks; scalar_t__ days; scalar_t__ hours; scalar_t__ minutes; scalar_t__ seconds; } ;
typedef  TYPE_1__ ldns_duration_type ;

/* Variables and functions */

int
ldns_duration_compare(const ldns_duration_type* d1, const ldns_duration_type* d2)
{
    if (!d1 && !d2) {
        return 0;
    }
    if (!d1 || !d2) {
        return d1?-1:1;
    }

    if (d1->years != d2->years) {
        return (int) (d1->years - d2->years);
    }
    if (d1->months != d2->months) {
        return (int) (d1->months - d2->months);
    }
    if (d1->weeks != d2->weeks) {
        return (int) (d1->weeks - d2->weeks);
    }
    if (d1->days != d2->days) {
        return (int) (d1->days - d2->days);
    }
    if (d1->hours != d2->hours) {
        return (int) (d1->hours - d2->hours);
    }
    if (d1->minutes != d2->minutes) {
        return (int) (d1->minutes - d2->minutes);
    }
    if (d1->seconds != d2->seconds) {
        return (int) (d1->seconds - d2->seconds);
    }

    return 0;
}