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
struct TYPE_4__ {scalar_t__ seconds; scalar_t__ minutes; scalar_t__ hours; scalar_t__ days; scalar_t__ weeks; scalar_t__ months; scalar_t__ years; } ;
typedef  TYPE_1__ ldns_duration_type ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 

ldns_duration_type*
ldns_duration_create(void)
{
    ldns_duration_type* duration;

    duration = malloc(sizeof(ldns_duration_type));
    if (!duration) {
        return NULL;
    }
    duration->years = 0;
    duration->months = 0;
    duration->weeks = 0;
    duration->days = 0;
    duration->hours = 0;
    duration->minutes = 0;
    duration->seconds = 0;
    return duration;
}