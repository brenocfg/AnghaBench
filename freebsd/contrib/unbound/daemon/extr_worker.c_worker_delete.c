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
struct TYPE_2__ {int /*<<< orphan*/  scratch; int /*<<< orphan*/  probe_timer; int /*<<< orphan*/  hints; int /*<<< orphan*/  fwds; int /*<<< orphan*/  scratch_buffer; scalar_t__ mesh; } ;
struct worker {scalar_t__ thread_num; int /*<<< orphan*/  scratchpad; TYPE_1__ env; int /*<<< orphan*/  alloc; int /*<<< orphan*/  rndstate; int /*<<< orphan*/  base; struct worker* ports; int /*<<< orphan*/  stat_timer; int /*<<< orphan*/  cmd; int /*<<< orphan*/  comsig; int /*<<< orphan*/  back; int /*<<< orphan*/  front; int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 scalar_t__ VERB_OPS ; 
 int /*<<< orphan*/  alloc_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  comm_base_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comm_signal_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comm_timer_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  forwards_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct worker*) ; 
 int /*<<< orphan*/  hints_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listen_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mesh_delete (scalar_t__) ; 
 int /*<<< orphan*/  mesh_stats (scalar_t__,char*) ; 
 int /*<<< orphan*/  outside_network_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outside_network_quit_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regional_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_stats_log (int /*<<< orphan*/ *,struct worker*,scalar_t__) ; 
 int /*<<< orphan*/  sldns_buffer_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tube_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ub_randfree (int /*<<< orphan*/ ) ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  worker_mem_report (struct worker*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wsvc_desetup_worker (struct worker*) ; 

void 
worker_delete(struct worker* worker)
{
	if(!worker) 
		return;
	if(worker->env.mesh && verbosity >= VERB_OPS) {
		server_stats_log(&worker->stats, worker, worker->thread_num);
		mesh_stats(worker->env.mesh, "mesh has");
		worker_mem_report(worker, NULL);
	}
	outside_network_quit_prepare(worker->back);
	mesh_delete(worker->env.mesh);
	sldns_buffer_free(worker->env.scratch_buffer);
	forwards_delete(worker->env.fwds);
	hints_delete(worker->env.hints);
	listen_delete(worker->front);
	outside_network_delete(worker->back);
	comm_signal_delete(worker->comsig);
	tube_delete(worker->cmd);
	comm_timer_delete(worker->stat_timer);
	comm_timer_delete(worker->env.probe_timer);
	free(worker->ports);
	if(worker->thread_num == 0) {
#ifdef UB_ON_WINDOWS
		wsvc_desetup_worker(worker);
#endif /* UB_ON_WINDOWS */
	}
	comm_base_delete(worker->base);
	ub_randfree(worker->rndstate);
	alloc_clear(&worker->alloc);
	regional_destroy(worker->env.scratch);
	regional_destroy(worker->scratchpad);
	free(worker);
}