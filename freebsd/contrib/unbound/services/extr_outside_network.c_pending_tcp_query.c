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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  unsigned int uint16_t ;
struct waiting_tcp {struct waiting_tcp* next_waiting; scalar_t__ pkt_len; int /*<<< orphan*/ * pkt; int /*<<< orphan*/  timer; int /*<<< orphan*/  tls_auth_name; int /*<<< orphan*/  ssl_upstream; void* cb_arg; int /*<<< orphan*/ * cb; TYPE_1__* outnet; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
struct timeval {int tv_sec; int tv_usec; } ;
struct serviced_query {TYPE_1__* outnet; int /*<<< orphan*/  zonelen; int /*<<< orphan*/  zone; int /*<<< orphan*/  addr; int /*<<< orphan*/  tls_auth_name; int /*<<< orphan*/  ssl_upstream; int /*<<< orphan*/  addrlen; } ;
struct pending_tcp {int dummy; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  comm_point_callback_type ;
struct TYPE_4__ {scalar_t__ log_forwarder_query_messages; scalar_t__ log_resolver_query_messages; } ;
struct TYPE_3__ {struct waiting_tcp* tcp_wait_last; struct waiting_tcp* tcp_wait_first; TYPE_2__* dtenv; int /*<<< orphan*/  rnd; int /*<<< orphan*/  base; struct pending_tcp* tcp_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_ID_SET (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  comm_tcp ; 
 int /*<<< orphan*/  comm_timer_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct waiting_tcp*) ; 
 int /*<<< orphan*/  comm_timer_set (int /*<<< orphan*/ ,struct timeval*) ; 
 int /*<<< orphan*/  dt_msg_send_outside_query (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct waiting_tcp*) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outnet_tcp_take_into_use (struct waiting_tcp*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outnet_tcptimer ; 
 int /*<<< orphan*/  sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_limit (int /*<<< orphan*/ *) ; 
 scalar_t__ ub_random (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waiting_tcp_delete (struct waiting_tcp*) ; 

struct waiting_tcp*
pending_tcp_query(struct serviced_query* sq, sldns_buffer* packet,
	int timeout, comm_point_callback_type* callback, void* callback_arg)
{
	struct pending_tcp* pend = sq->outnet->tcp_free;
	struct waiting_tcp* w;
	struct timeval tv;
	uint16_t id;
	/* if no buffer is free allocate space to store query */
	w = (struct waiting_tcp*)malloc(sizeof(struct waiting_tcp) 
		+ (pend?0:sldns_buffer_limit(packet)));
	if(!w) {
		return NULL;
	}
	if(!(w->timer = comm_timer_create(sq->outnet->base, outnet_tcptimer, w))) {
		free(w);
		return NULL;
	}
	w->pkt = NULL;
	w->pkt_len = 0;
	id = ((unsigned)ub_random(sq->outnet->rnd)>>8) & 0xffff;
	LDNS_ID_SET(sldns_buffer_begin(packet), id);
	memcpy(&w->addr, &sq->addr, sq->addrlen);
	w->addrlen = sq->addrlen;
	w->outnet = sq->outnet;
	w->cb = callback;
	w->cb_arg = callback_arg;
	w->ssl_upstream = sq->ssl_upstream;
	w->tls_auth_name = sq->tls_auth_name;
#ifndef S_SPLINT_S
	tv.tv_sec = timeout/1000;
	tv.tv_usec = (timeout%1000)*1000;
#endif
	comm_timer_set(w->timer, &tv);
	if(pend) {
		/* we have a buffer available right now */
		if(!outnet_tcp_take_into_use(w, sldns_buffer_begin(packet),
			sldns_buffer_limit(packet))) {
			waiting_tcp_delete(w);
			return NULL;
		}
#ifdef USE_DNSTAP
		if(sq->outnet->dtenv &&
		   (sq->outnet->dtenv->log_resolver_query_messages ||
		    sq->outnet->dtenv->log_forwarder_query_messages))
		dt_msg_send_outside_query(sq->outnet->dtenv, &sq->addr,
		comm_tcp, sq->zone, sq->zonelen, packet);
#endif
	} else {
		/* queue up */
		w->pkt = (uint8_t*)w + sizeof(struct waiting_tcp);
		w->pkt_len = sldns_buffer_limit(packet);
		memmove(w->pkt, sldns_buffer_begin(packet), w->pkt_len);
		w->next_waiting = NULL;
		if(sq->outnet->tcp_wait_last)
			sq->outnet->tcp_wait_last->next_waiting = w;
		else	sq->outnet->tcp_wait_first = w;
		sq->outnet->tcp_wait_last = w;
	}
	return w;
}