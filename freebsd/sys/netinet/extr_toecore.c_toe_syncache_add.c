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
struct tcpopt {int dummy; } ;
struct tcphdr {int dummy; } ;
struct socket {int dummy; } ;
struct inpcb {struct socket* inp_socket; } ;
struct in_conninfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcb*) ; 
 int /*<<< orphan*/  syncache_add (struct in_conninfo*,struct tcpopt*,struct tcphdr*,struct inpcb*,struct socket**,int /*<<< orphan*/ *,void*,void*) ; 

void
toe_syncache_add(struct in_conninfo *inc, struct tcpopt *to, struct tcphdr *th,
    struct inpcb *inp, void *tod, void *todctx)
{
	struct socket *lso = inp->inp_socket;

	INP_WLOCK_ASSERT(inp);

	syncache_add(inc, to, th, inp, &lso, NULL, tod, todctx);
}