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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ time_started; int /*<<< orphan*/  sum; } ;
typedef  TYPE_1__ perf_timer ;

/* Variables and functions */
 scalar_t__ now_in_ms () ; 

void perf__timer__stop(perf_timer *t)
{
	uint32_t now = now_in_ms();
	t->sum += (now - t->time_started);
}