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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct worker {TYPE_2__* back; } ;
struct sockaddr_storage {int dummy; } ;
struct query_info {int dummy; } ;
struct outbound_entry {int /*<<< orphan*/  qsent; struct module_qstate* qstate; } ;
struct module_qstate {TYPE_3__* env; int /*<<< orphan*/  region; } ;
typedef  int /*<<< orphan*/  socklen_t ;
struct TYPE_6__ {TYPE_1__* cfg; struct worker* worker; } ;
struct TYPE_5__ {int /*<<< orphan*/  udp_buff; } ;
struct TYPE_4__ {int /*<<< orphan*/  tcp_upstream; } ;

/* Variables and functions */
 int /*<<< orphan*/  outnet_serviced_query (TYPE_2__*,struct query_info*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,char*,struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,struct module_qstate*,int /*<<< orphan*/ ,struct outbound_entry*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ regional_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  worker_handle_service_reply ; 

struct outbound_entry*
worker_send_query(struct query_info* qinfo, uint16_t flags, int dnssec,
	int want_dnssec, int nocaps, struct sockaddr_storage* addr,
	socklen_t addrlen, uint8_t* zone, size_t zonelen, int ssl_upstream,
	char* tls_auth_name, struct module_qstate* q)
{
	struct worker* worker = q->env->worker;
	struct outbound_entry* e = (struct outbound_entry*)regional_alloc(
		q->region, sizeof(*e));
	if(!e) 
		return NULL;
	e->qstate = q;
	e->qsent = outnet_serviced_query(worker->back, qinfo, flags, dnssec,
		want_dnssec, nocaps, q->env->cfg->tcp_upstream,
		ssl_upstream, tls_auth_name, addr, addrlen, zone, zonelen, q,
		worker_handle_service_reply, e, worker->back->udp_buff, q->env);
	if(!e->qsent) {
		return NULL;
	}
	return e;
}