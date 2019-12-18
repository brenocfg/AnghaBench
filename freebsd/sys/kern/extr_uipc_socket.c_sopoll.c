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
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct socket {TYPE_2__* so_proto; } ;
struct TYPE_4__ {TYPE_1__* pr_usrreqs; } ;
struct TYPE_3__ {int (* pru_sopoll ) (struct socket*,int,struct ucred*,struct thread*) ;} ;

/* Variables and functions */
 int stub1 (struct socket*,int,struct ucred*,struct thread*) ; 

int
sopoll(struct socket *so, int events, struct ucred *active_cred,
    struct thread *td)
{

	/*
	 * We do not need to set or assert curvnet as long as everyone uses
	 * sopoll_generic().
	 */
	return (so->so_proto->pr_usrreqs->pru_sopoll(so, events, active_cred,
	    td));
}