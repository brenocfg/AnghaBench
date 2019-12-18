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
struct worker {int thread_num; TYPE_2__* daemon; int /*<<< orphan*/  cmd; } ;
struct TYPE_4__ {int num_ports; int /*<<< orphan*/ * ports; TYPE_1__* cfg; } ;
struct TYPE_3__ {scalar_t__ so_reuseport; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_other_pipes (TYPE_2__*,int) ; 
 int /*<<< orphan*/  fatal_exit (char*) ; 
 int /*<<< orphan*/  log_thread_set (int*) ; 
 int /*<<< orphan*/  tube_close_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ub_thread_blocksigs () ; 
 int /*<<< orphan*/  worker_init (struct worker*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  worker_work (struct worker*) ; 

__attribute__((used)) static void* 
thread_start(void* arg)
{
	struct worker* worker = (struct worker*)arg;
	int port_num = 0;
	log_thread_set(&worker->thread_num);
	ub_thread_blocksigs();
#ifdef THREADS_DISABLED
	/* close pipe ends used by main */
	tube_close_write(worker->cmd);
	close_other_pipes(worker->daemon, worker->thread_num);
#endif
#ifdef SO_REUSEPORT
	if(worker->daemon->cfg->so_reuseport)
		port_num = worker->thread_num % worker->daemon->num_ports;
	else
		port_num = 0;
#endif
	if(!worker_init(worker, worker->daemon->cfg,
			worker->daemon->ports[port_num], 0))
		fatal_exit("Could not initialize thread");

	worker_work(worker);
	return NULL;
}