#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_4__ {int /*<<< orphan*/  generalTime; int /*<<< orphan*/  utcTime; } ;
struct TYPE_5__ {int element; TYPE_1__ u; } ;
typedef  TYPE_2__ Time ;

/* Variables and functions */
#define  choice_Time_generalTime 129 
#define  choice_Time_utcTime 128 

time_t
_hx509_Time2time_t(const Time *t)
{
    switch(t->element) {
    case choice_Time_utcTime:
	return t->u.utcTime;
    case choice_Time_generalTime:
	return t->u.generalTime;
    }
    return 0;
}