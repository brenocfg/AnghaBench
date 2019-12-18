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
struct unpcb {int /*<<< orphan*/ * unp_conn; } ;
struct thread {int dummy; } ;
struct socket {struct unpcb* so_pcb; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int EISCONN ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  UNP_PCB_LOCK (struct unpcb*) ; 
 int /*<<< orphan*/  UNP_PCB_UNLOCK (struct unpcb*) ; 
 int unp_connect (struct socket*,struct sockaddr*,struct thread*) ; 

__attribute__((used)) static int
connect_internal(struct socket *so, struct sockaddr *nam, struct thread *td)
{
	int error;
	struct unpcb *unp;

	unp = so->so_pcb;
	if (unp->unp_conn != NULL)
		return (EISCONN);
	error = unp_connect(so, nam, td);
	if (error)
		return (error);
	UNP_PCB_LOCK(unp);
	if (unp->unp_conn == NULL) {
		UNP_PCB_UNLOCK(unp);
		if (error == 0)
			error = ENOTCONN;
	}
	return (error);
}