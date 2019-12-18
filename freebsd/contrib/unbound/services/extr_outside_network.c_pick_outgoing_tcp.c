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
struct waiting_tcp {TYPE_1__* outnet; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
struct sockaddr_in6 {scalar_t__ sin6_port; } ;
struct sockaddr_in {scalar_t__ sin_port; } ;
struct sockaddr {int dummy; } ;
struct port_if {int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int num_ip6; int num_ip4; int /*<<< orphan*/  rnd; struct port_if* ip4_ifs; struct port_if* ip6_ifs; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  VERB_OPS ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 scalar_t__ addr_is_any (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ addr_is_ip6 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bind (int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_addr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_assert (struct port_if*) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 size_t ub_random_max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wsa_strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pick_outgoing_tcp(struct waiting_tcp* w, int s)
{
	struct port_if* pi = NULL;
	int num;
#ifdef INET6
	if(addr_is_ip6(&w->addr, w->addrlen))
		num = w->outnet->num_ip6;
	else
#endif
		num = w->outnet->num_ip4;
	if(num == 0) {
		log_err("no TCP outgoing interfaces of family");
		log_addr(VERB_OPS, "for addr", &w->addr, w->addrlen);
#ifndef USE_WINSOCK
		close(s);
#else
		closesocket(s);
#endif
		return 0;
	}
#ifdef INET6
	if(addr_is_ip6(&w->addr, w->addrlen))
		pi = &w->outnet->ip6_ifs[ub_random_max(w->outnet->rnd, num)];
	else
#endif
		pi = &w->outnet->ip4_ifs[ub_random_max(w->outnet->rnd, num)];
	log_assert(pi);
	if(addr_is_any(&pi->addr, pi->addrlen)) {
		/* binding to the ANY interface is for listening sockets */
		return 1;
	}
	/* set port to 0 */
	if(addr_is_ip6(&pi->addr, pi->addrlen))
		((struct sockaddr_in6*)&pi->addr)->sin6_port = 0;
	else	((struct sockaddr_in*)&pi->addr)->sin_port = 0;
	if(bind(s, (struct sockaddr*)&pi->addr, pi->addrlen) != 0) {
#ifndef USE_WINSOCK
		log_err("outgoing tcp: bind: %s", strerror(errno));
		close(s);
#else
		log_err("outgoing tcp: bind: %s", 
			wsa_strerror(WSAGetLastError()));
		closesocket(s);
#endif
		return 0;
	}
	log_addr(VERB_ALGO, "tcp bound to src", &pi->addr, pi->addrlen);
	return 1;
}