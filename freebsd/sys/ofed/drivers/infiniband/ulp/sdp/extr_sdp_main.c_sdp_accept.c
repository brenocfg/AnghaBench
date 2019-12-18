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
struct socket {int so_state; } ;
struct sockaddr {int dummy; } ;
struct sdp_sock {int flags; scalar_t__ faddr; scalar_t__ fport; } ;
struct in_addr {scalar_t__ s_addr; } ;
typedef  scalar_t__ in_port_t ;

/* Variables and functions */
 int ECONNABORTED ; 
 int SDP_DROPPED ; 
 int SDP_TIMEWAIT ; 
 int /*<<< orphan*/  SDP_WLOCK (struct sdp_sock*) ; 
 int /*<<< orphan*/  SDP_WUNLOCK (struct sdp_sock*) ; 
 int SS_ISDISCONNECTED ; 
 struct sdp_sock* sdp_sk (struct socket*) ; 
 struct sockaddr* sdp_sockaddr (scalar_t__,struct in_addr*) ; 

__attribute__((used)) static int
sdp_accept(struct socket *so, struct sockaddr **nam)
{
	struct sdp_sock *ssk = NULL;
	struct in_addr addr;
	in_port_t port;
	int error;

	if (so->so_state & SS_ISDISCONNECTED)
		return (ECONNABORTED);

	port = 0;
	addr.s_addr = 0;
	error = 0;
	ssk = sdp_sk(so);
	SDP_WLOCK(ssk);
	if (ssk->flags & (SDP_TIMEWAIT | SDP_DROPPED)) {
		error = ECONNABORTED;
		goto out;
	}
	port = ssk->fport;
	addr.s_addr = ssk->faddr;
out:
	SDP_WUNLOCK(ssk);
	if (error == 0)
		*nam = sdp_sockaddr(port, &addr);
	return error;
}