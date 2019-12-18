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
struct comm_reply {TYPE_2__* c; } ;
struct TYPE_4__ {scalar_t__ type; TYPE_1__* tcp_req_info; } ;
struct TYPE_3__ {int is_drop; } ;

/* Variables and functions */
 scalar_t__ comm_tcp_accept ; 
 scalar_t__ comm_udp ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  reclaim_tcp_handler (TYPE_2__*) ; 

void 
comm_point_drop_reply(struct comm_reply* repinfo)
{
	if(!repinfo)
		return;
	log_assert(repinfo && repinfo->c);
	log_assert(repinfo->c->type != comm_tcp_accept);
	if(repinfo->c->type == comm_udp)
		return;
	if(repinfo->c->tcp_req_info)
		repinfo->c->tcp_req_info->is_drop = 1;
	reclaim_tcp_handler(repinfo->c);
}