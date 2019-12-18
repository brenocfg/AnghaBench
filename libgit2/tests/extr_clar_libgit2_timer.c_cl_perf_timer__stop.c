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
struct TYPE_3__ {scalar_t__ last; int /*<<< orphan*/  sum; scalar_t__ time_started; } ;
typedef  TYPE_1__ cl_perf_timer ;

/* Variables and functions */
 double git__timer () ; 

void cl_perf_timer__stop(cl_perf_timer *t)
{
	double time_now = git__timer();

	t->last = time_now - t->time_started;
	t->sum += t->last;
}