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
struct inpcb {int /*<<< orphan*/ * inp_socket; } ;
struct epoch_tracker {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_INFO_WLOCKED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INP_WLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 int /*<<< orphan*/  V_tcbinfo ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 int /*<<< orphan*/  tcp_detach (struct socket*,struct inpcb*) ; 

__attribute__((used)) static void
tcp_usr_detach(struct socket *so)
{
	struct inpcb *inp;
	int rlock = 0;
	struct epoch_tracker et;

	inp = sotoinpcb(so);
	KASSERT(inp != NULL, ("tcp_usr_detach: inp == NULL"));
	if (!INP_INFO_WLOCKED(&V_tcbinfo)) {
		NET_EPOCH_ENTER(et);
		rlock = 1;
	}
	INP_WLOCK(inp);
	KASSERT(inp->inp_socket != NULL,
	    ("tcp_usr_detach: inp_socket == NULL"));
	tcp_detach(so, inp);
	if (rlock)
		NET_EPOCH_EXIT(et);
}