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
typedef  scalar_t__ time_t ;
struct TYPE_2__ {int /*<<< orphan*/  probe_timer; } ;
struct worker {TYPE_1__ env; } ;
struct timeval {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;

/* Variables and functions */
 scalar_t__ autr_probe_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  comm_timer_set (int /*<<< orphan*/ ,struct timeval*) ; 

void worker_probe_timer_cb(void* arg)
{
	struct worker* worker = (struct worker*)arg;
	struct timeval tv;
#ifndef S_SPLINT_S
	tv.tv_sec = (time_t)autr_probe_timer(&worker->env);
	tv.tv_usec = 0;
#endif
	if(tv.tv_sec != 0)
		comm_timer_set(worker->env.probe_timer, &tv);
}