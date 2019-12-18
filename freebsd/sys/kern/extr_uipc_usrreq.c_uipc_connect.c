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
struct thread {int dummy; } ;
struct socket {int dummy; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct thread* curthread ; 
 int unp_connect (struct socket*,struct sockaddr*,struct thread*) ; 

__attribute__((used)) static int
uipc_connect(struct socket *so, struct sockaddr *nam, struct thread *td)
{
	int error;

	KASSERT(td == curthread, ("uipc_connect: td != curthread"));
	error = unp_connect(so, nam, td);
	return (error);
}