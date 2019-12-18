#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mesh; } ;
struct worker {TYPE_2__* daemon; TYPE_1__ env; int /*<<< orphan*/  thread_num; int /*<<< orphan*/  stats; } ;
struct TYPE_6__ {int /*<<< orphan*/  stat_cumulative; scalar_t__ shm_enable; } ;
struct TYPE_5__ {TYPE_3__* cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  mesh_stats (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  server_stats_log (int /*<<< orphan*/ *,struct worker*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shm_main_run (struct worker*) ; 
 int /*<<< orphan*/  worker_mem_report (struct worker*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  worker_restart_timer (struct worker*) ; 
 int /*<<< orphan*/  worker_stats_clear (struct worker*) ; 

void worker_stat_timer_cb(void* arg)
{
	struct worker* worker = (struct worker*)arg;
	server_stats_log(&worker->stats, worker, worker->thread_num);
	mesh_stats(worker->env.mesh, "mesh has");
	worker_mem_report(worker, NULL);
	/* SHM is enabled, process data to SHM */
	if (worker->daemon->cfg->shm_enable) {
		shm_main_run(worker);
	}
	if(!worker->daemon->cfg->stat_cumulative) {
		worker_stats_clear(worker);
	}
	/* start next timer */
	worker_restart_timer(worker);
}