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
struct socket {scalar_t__ so_count; int so_state; TYPE_2__* so_proto; } ;
struct TYPE_4__ {TYPE_1__* pr_usrreqs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* pru_abort ) (struct socket*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int SS_NOFDREF ; 
 int SS_PROTOREF ; 
 int /*<<< orphan*/  VNET_SO_ASSERT (struct socket*) ; 
 int /*<<< orphan*/  sofree (struct socket*) ; 
 int /*<<< orphan*/  stub1 (struct socket*) ; 

void
soabort(struct socket *so)
{

	/*
	 * In as much as is possible, assert that no references to this
	 * socket are held.  This is not quite the same as asserting that the
	 * current thread is responsible for arranging for no references, but
	 * is as close as we can get for now.
	 */
	KASSERT(so->so_count == 0, ("soabort: so_count"));
	KASSERT((so->so_state & SS_PROTOREF) == 0, ("soabort: SS_PROTOREF"));
	KASSERT(so->so_state & SS_NOFDREF, ("soabort: !SS_NOFDREF"));
	VNET_SO_ASSERT(so);

	if (so->so_proto->pr_usrreqs->pru_abort != NULL)
		(*so->so_proto->pr_usrreqs->pru_abort)(so);
	SOCK_LOCK(so);
	sofree(so);
}