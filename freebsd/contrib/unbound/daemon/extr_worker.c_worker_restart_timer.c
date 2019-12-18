#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* cfg; } ;
struct worker {int /*<<< orphan*/  stat_timer; TYPE_2__ env; } ;
struct timeval {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_3__ {scalar_t__ stat_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  comm_timer_set (int /*<<< orphan*/ ,struct timeval*) ; 

__attribute__((used)) static void
worker_restart_timer(struct worker* worker)
{
	if(worker->env.cfg->stat_interval > 0) {
		struct timeval tv;
#ifndef S_SPLINT_S
		tv.tv_sec = worker->env.cfg->stat_interval;
		tv.tv_usec = 0;
#endif
		comm_timer_set(worker->stat_timer, &tv);
	}
}