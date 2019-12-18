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
struct TYPE_3__ {int /*<<< orphan*/  si_note; } ;
struct socket {int so_options; short so_state; TYPE_1__ so_rdsel; } ;
struct TYPE_4__ {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KNOTE_UNLOCKED (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOLISTEN_LOCK (struct socket*) ; 
 int SO_ACCEPTCONN ; 
 short SS_NBIO ; 
 TYPE_2__* curthread ; 
 int mac_socket_check_accept (int /*<<< orphan*/ ,struct socket*) ; 
 int solisten_dequeue (struct socket*,struct socket**,int /*<<< orphan*/ ) ; 

int
svc_vc_accept(struct socket *head, struct socket **sop)
{
	struct socket *so;
	int error = 0;
	short nbio;

	/* XXXGL: shouldn't that be an assertion? */
	if ((head->so_options & SO_ACCEPTCONN) == 0) {
		error = EINVAL;
		goto done;
	}
#ifdef MAC
	error = mac_socket_check_accept(curthread->td_ucred, head);
	if (error != 0)
		goto done;
#endif
	/*
	 * XXXGL: we want non-blocking semantics.  The socket could be a
	 * socket created by kernel as well as socket shared with userland,
	 * so we can't be sure about presense of SS_NBIO.  We also shall not
	 * toggle it on the socket, since that may surprise userland.  So we
	 * set SS_NBIO only temporarily.
	 */
	SOLISTEN_LOCK(head);
	nbio = head->so_state & SS_NBIO;
	head->so_state |= SS_NBIO;
	error = solisten_dequeue(head, &so, 0);
	head->so_state &= (nbio & ~SS_NBIO);
	if (error)
		goto done;

	so->so_state |= nbio;
	*sop = so;

	/* connection has been removed from the listen queue */
	KNOTE_UNLOCKED(&head->so_rdsel.si_note, 0);
done:
	return (error);
}