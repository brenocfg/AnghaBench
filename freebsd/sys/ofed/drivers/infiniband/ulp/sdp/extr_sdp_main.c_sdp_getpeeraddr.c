#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct socket {int dummy; } ;
struct sockaddr {int dummy; } ;
struct sdp_sock {int /*<<< orphan*/  faddr; int /*<<< orphan*/  fport; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
typedef  int /*<<< orphan*/  in_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  SDP_RLOCK (struct sdp_sock*) ; 
 int /*<<< orphan*/  SDP_RUNLOCK (struct sdp_sock*) ; 
 struct sdp_sock* sdp_sk (struct socket*) ; 
 struct sockaddr* sdp_sockaddr (int /*<<< orphan*/ ,struct in_addr*) ; 

__attribute__((used)) static int
sdp_getpeeraddr(struct socket *so, struct sockaddr **nam)
{
	struct sdp_sock *ssk;
	struct in_addr addr;
	in_port_t port;

	ssk = sdp_sk(so);
	SDP_RLOCK(ssk);
	port = ssk->fport;
	addr.s_addr = ssk->faddr;
	SDP_RUNLOCK(ssk);

	*nam = sdp_sockaddr(port, &addr);
	return 0;
}