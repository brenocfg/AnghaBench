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
typedef  int /*<<< orphan*/ * udp_tun_icmp_t ;
typedef  int /*<<< orphan*/ * udp_tun_func_t ;
struct udpcb {void* u_tun_ctx; int /*<<< orphan*/ * u_icmp_func; int /*<<< orphan*/ * u_tun_func; } ;
struct socket {scalar_t__ so_type; } ;
struct inpcb {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  INP_WLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ SOCK_DGRAM ; 
 struct udpcb* intoudpcb (struct inpcb*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

int
udp_set_kernel_tunneling(struct socket *so, udp_tun_func_t f, udp_tun_icmp_t i, void *ctx)
{
	struct inpcb *inp;
	struct udpcb *up;

	KASSERT(so->so_type == SOCK_DGRAM,
	    ("udp_set_kernel_tunneling: !dgram"));
	inp = sotoinpcb(so);
	KASSERT(inp != NULL, ("udp_set_kernel_tunneling: inp == NULL"));
	INP_WLOCK(inp);
	up = intoudpcb(inp);
	if ((up->u_tun_func != NULL) ||
	    (up->u_icmp_func != NULL)) {
		INP_WUNLOCK(inp);
		return (EBUSY);
	}
	up->u_tun_func = f;
	up->u_icmp_func = i;
	up->u_tun_ctx = ctx;
	INP_WUNLOCK(inp);
	return (0);
}