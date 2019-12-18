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
struct unpcb {int unp_flags; int /*<<< orphan*/  unp_peercred; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int UNP_HAVEPC ; 
 int UNP_WANTCRED ; 
 int /*<<< orphan*/  cru2xt (struct thread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
unp_copy_peercred(struct thread *td, struct unpcb *client_unp,
    struct unpcb *server_unp, struct unpcb *listen_unp)
{
	cru2xt(td, &client_unp->unp_peercred);
	client_unp->unp_flags |= UNP_HAVEPC;

	memcpy(&server_unp->unp_peercred, &listen_unp->unp_peercred,
	    sizeof(server_unp->unp_peercred));
	server_unp->unp_flags |= UNP_HAVEPC;
	if (listen_unp->unp_flags & UNP_WANTCRED)
		client_unp->unp_flags |= UNP_WANTCRED;
}