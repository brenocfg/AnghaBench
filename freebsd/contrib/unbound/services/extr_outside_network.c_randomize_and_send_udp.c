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
struct timeval {int tv_sec; int tv_usec; } ;
struct sockaddr {int dummy; } ;
struct pending {TYPE_1__* sq; int /*<<< orphan*/  addr; int /*<<< orphan*/  timer; TYPE_2__* pc; int /*<<< orphan*/  addrlen; } ;
struct outside_network {TYPE_3__* dtenv; int /*<<< orphan*/  ip4_ifs; int /*<<< orphan*/  num_ip4; int /*<<< orphan*/  ip6_ifs; int /*<<< orphan*/  num_ip6; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
struct TYPE_6__ {scalar_t__ log_forwarder_query_messages; scalar_t__ log_resolver_query_messages; } ;
struct TYPE_5__ {scalar_t__ cp; } ;
struct TYPE_4__ {int /*<<< orphan*/  zonelen; int /*<<< orphan*/  zone; struct outside_network* outnet; } ;

/* Variables and functions */
 scalar_t__ addr_is_ip6 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comm_point_send_udp_msg (scalar_t__,int /*<<< orphan*/ *,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comm_timer_set (int /*<<< orphan*/ ,struct timeval*) ; 
 int /*<<< orphan*/  comm_udp ; 
 int /*<<< orphan*/  dt_msg_send_outside_query (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  portcomm_loweruse (struct outside_network*,TYPE_2__*) ; 
 int /*<<< orphan*/  select_id (struct outside_network*,struct pending*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  select_ifport (struct outside_network*,struct pending*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
randomize_and_send_udp(struct pending* pend, sldns_buffer* packet, int timeout)
{
	struct timeval tv;
	struct outside_network* outnet = pend->sq->outnet;

	/* select id */
	if(!select_id(outnet, pend, packet)) {
		return 0;
	}

	/* select src_if, port */
	if(addr_is_ip6(&pend->addr, pend->addrlen)) {
		if(!select_ifport(outnet, pend, 
			outnet->num_ip6, outnet->ip6_ifs))
			return 0;
	} else {
		if(!select_ifport(outnet, pend, 
			outnet->num_ip4, outnet->ip4_ifs))
			return 0;
	}
	log_assert(pend->pc && pend->pc->cp);

	/* send it over the commlink */
	if(!comm_point_send_udp_msg(pend->pc->cp, packet, 
		(struct sockaddr*)&pend->addr, pend->addrlen)) {
		portcomm_loweruse(outnet, pend->pc);
		return 0;
	}

	/* system calls to set timeout after sending UDP to make roundtrip
	   smaller. */
#ifndef S_SPLINT_S
	tv.tv_sec = timeout/1000;
	tv.tv_usec = (timeout%1000)*1000;
#endif
	comm_timer_set(pend->timer, &tv);

#ifdef USE_DNSTAP
	if(outnet->dtenv &&
	   (outnet->dtenv->log_resolver_query_messages ||
	    outnet->dtenv->log_forwarder_query_messages))
		dt_msg_send_outside_query(outnet->dtenv, &pend->addr, comm_udp,
		pend->sq->zone, pend->sq->zonelen, packet);
#endif
	return 1;
}