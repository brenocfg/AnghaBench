#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {scalar_t__ sb_cc; } ;
struct socket {int so_options; scalar_t__ so_linger; int /*<<< orphan*/ * so_pcb; TYPE_1__ so_rcv; TYPE_1__ so_snd; } ;
struct sctp_inpcb {int sctp_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_CALLED_AFTER_CMPSET_OFCLOSE ; 
 int /*<<< orphan*/  SCTP_FREE_SHOULD_USE_ABORT ; 
 int /*<<< orphan*/  SCTP_FREE_SHOULD_USE_GRACEFUL_CLOSE ; 
 int SCTP_PCB_FLAGS_CLOSE_IP ; 
 int SCTP_PCB_FLAGS_SOCKET_GONE ; 
 int /*<<< orphan*/  SCTP_SB_CLEAR (TYPE_1__) ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int /*<<< orphan*/  SOCK_UNLOCK (struct socket*) ; 
 int SO_LINGER ; 
 scalar_t__ atomic_cmpset_int (int*,int,int) ; 
 int /*<<< orphan*/  sctp_inpcb_free (struct sctp_inpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_log_closing (struct sctp_inpcb*,int /*<<< orphan*/ *,int) ; 

void
sctp_close(struct socket *so)
{
	struct sctp_inpcb *inp;
	uint32_t flags;

	inp = (struct sctp_inpcb *)so->so_pcb;
	if (inp == NULL)
		return;

	/*
	 * Inform all the lower layer assoc that we are done.
	 */
sctp_must_try_again:
	flags = inp->sctp_flags;
#ifdef SCTP_LOG_CLOSING
	sctp_log_closing(inp, NULL, 17);
#endif
	if (((flags & SCTP_PCB_FLAGS_SOCKET_GONE) == 0) &&
	    (atomic_cmpset_int(&inp->sctp_flags, flags, (flags | SCTP_PCB_FLAGS_SOCKET_GONE | SCTP_PCB_FLAGS_CLOSE_IP)))) {
		if (((so->so_options & SO_LINGER) && (so->so_linger == 0)) ||
		    (so->so_rcv.sb_cc > 0)) {
#ifdef SCTP_LOG_CLOSING
			sctp_log_closing(inp, NULL, 13);
#endif
			sctp_inpcb_free(inp, SCTP_FREE_SHOULD_USE_ABORT,
			    SCTP_CALLED_AFTER_CMPSET_OFCLOSE);
		} else {
#ifdef SCTP_LOG_CLOSING
			sctp_log_closing(inp, NULL, 14);
#endif
			sctp_inpcb_free(inp, SCTP_FREE_SHOULD_USE_GRACEFUL_CLOSE,
			    SCTP_CALLED_AFTER_CMPSET_OFCLOSE);
		}
		/*
		 * The socket is now detached, no matter what the state of
		 * the SCTP association.
		 */
		SOCK_LOCK(so);
		SCTP_SB_CLEAR(so->so_snd);
		/*
		 * same for the rcv ones, they are only here for the
		 * accounting/select.
		 */
		SCTP_SB_CLEAR(so->so_rcv);

		/* Now null out the reference, we are completely detached. */
		so->so_pcb = NULL;
		SOCK_UNLOCK(so);
	} else {
		flags = inp->sctp_flags;
		if ((flags & SCTP_PCB_FLAGS_SOCKET_GONE) == 0) {
			goto sctp_must_try_again;
		}
	}
	return;
}