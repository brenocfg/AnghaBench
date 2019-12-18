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
struct inpcb {int /*<<< orphan*/  in6p_faddr; } ;

/* Variables and functions */
 int ENOTCONN ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int SS_ISCONNECTED ; 
 int /*<<< orphan*/  in6addr_any ; 
 int /*<<< orphan*/  rip6_abort (struct socket*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

__attribute__((used)) static int
rip6_disconnect(struct socket *so)
{
	struct inpcb *inp;

	inp = sotoinpcb(so);
	KASSERT(inp != NULL, ("rip6_disconnect: inp == NULL"));

	if ((so->so_state & SS_ISCONNECTED) == 0)
		return (ENOTCONN);
	inp->in6p_faddr = in6addr_any;
	rip6_abort(so);
	return (0);
}