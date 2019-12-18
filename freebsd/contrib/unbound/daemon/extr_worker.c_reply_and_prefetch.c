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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ time_t ;
struct TYPE_4__ {int /*<<< orphan*/  mesh; } ;
struct worker {TYPE_1__ env; int /*<<< orphan*/  stats; } ;
struct query_info {int dummy; } ;
struct comm_reply {TYPE_2__* c; } ;
struct TYPE_6__ {int /*<<< orphan*/  spool_buffer; } ;
struct TYPE_5__ {int /*<<< orphan*/  buffer; TYPE_3__* tcp_req_info; } ;

/* Variables and functions */
 scalar_t__ PREFETCH_EXPIRY_ADD ; 
 int /*<<< orphan*/  comm_point_send_reply (struct comm_reply*) ; 
 int /*<<< orphan*/  mesh_new_prefetch (int /*<<< orphan*/ ,struct query_info*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  server_stats_prefetch (int /*<<< orphan*/ *,struct worker*) ; 
 int /*<<< orphan*/  sldns_buffer_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sldns_buffer_limit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
reply_and_prefetch(struct worker* worker, struct query_info* qinfo, 
	uint16_t flags, struct comm_reply* repinfo, time_t leeway)
{
	/* first send answer to client to keep its latency 
	 * as small as a cachereply */
	if(sldns_buffer_limit(repinfo->c->buffer) != 0) {
		if(repinfo->c->tcp_req_info) {
			sldns_buffer_copy(
				repinfo->c->tcp_req_info->spool_buffer,
				repinfo->c->buffer);
		}
		comm_point_send_reply(repinfo);
	}
	server_stats_prefetch(&worker->stats, worker);
	
	/* create the prefetch in the mesh as a normal lookup without
	 * client addrs waiting, which has the cache blacklisted (to bypass
	 * the cache and go to the network for the data). */
	/* this (potentially) runs the mesh for the new query */
	mesh_new_prefetch(worker->env.mesh, qinfo, flags, leeway + 
		PREFETCH_EXPIRY_ADD);
}