#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ state; } ;
struct pppThroughput {TYPE_1__ Timer; int /*<<< orphan*/  downtime; } ;

/* Variables and functions */
 scalar_t__ TIMER_STOPPED ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_Stop (TYPE_1__*) ; 

void
throughput_stop(struct pppThroughput *t)
{
  if (t->Timer.state != TIMER_STOPPED)
    time(&t->downtime);
  timer_Stop(&t->Timer);
}