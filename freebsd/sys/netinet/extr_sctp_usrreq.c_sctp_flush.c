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
struct TYPE_4__ {int /*<<< orphan*/ * sb_mb; scalar_t__ sb_mbcnt; scalar_t__ sb_cc; } ;
struct TYPE_3__ {int /*<<< orphan*/ * sb_mb; scalar_t__ sb_mbcnt; scalar_t__ sb_cc; } ;
struct socket {TYPE_2__ so_snd; TYPE_1__ so_rcv; scalar_t__ so_pcb; } ;
struct sctp_inpcb {int sctp_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int PRU_FLUSH_RD ; 
 int PRU_FLUSH_RDWR ; 
 int PRU_FLUSH_WR ; 
 int /*<<< orphan*/  SCTP_FROM_SCTP_USRREQ ; 
 int /*<<< orphan*/  SCTP_INP_READ_LOCK (struct sctp_inpcb*) ; 
 int /*<<< orphan*/  SCTP_INP_READ_UNLOCK (struct sctp_inpcb*) ; 
 int /*<<< orphan*/  SCTP_INP_RLOCK (struct sctp_inpcb*) ; 
 int /*<<< orphan*/  SCTP_INP_RUNLOCK (struct sctp_inpcb*) ; 
 int /*<<< orphan*/  SCTP_INP_WLOCK (struct sctp_inpcb*) ; 
 int /*<<< orphan*/  SCTP_INP_WUNLOCK (struct sctp_inpcb*) ; 
 int /*<<< orphan*/  SCTP_LTRACE_ERR_RET (struct sctp_inpcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int SCTP_PCB_FLAGS_SOCKET_CANT_READ ; 
 int SCTP_PCB_FLAGS_UDPTYPE ; 

int
sctp_flush(struct socket *so, int how)
{
	/*
	 * We will just clear out the values and let subsequent close clear
	 * out the data, if any. Note if the user did a shutdown(SHUT_RD)
	 * they will not be able to read the data, the socket will block
	 * that from happening.
	 */
	struct sctp_inpcb *inp;

	inp = (struct sctp_inpcb *)so->so_pcb;
	if (inp == NULL) {
		SCTP_LTRACE_ERR_RET(inp, NULL, NULL, SCTP_FROM_SCTP_USRREQ, EINVAL);
		return (EINVAL);
	}
	SCTP_INP_RLOCK(inp);
	/* For the 1 to many model this does nothing */
	if (inp->sctp_flags & SCTP_PCB_FLAGS_UDPTYPE) {
		SCTP_INP_RUNLOCK(inp);
		return (0);
	}
	SCTP_INP_RUNLOCK(inp);
	if ((how == PRU_FLUSH_RD) || (how == PRU_FLUSH_RDWR)) {
		/*
		 * First make sure the sb will be happy, we don't use these
		 * except maybe the count
		 */
		SCTP_INP_WLOCK(inp);
		SCTP_INP_READ_LOCK(inp);
		inp->sctp_flags |= SCTP_PCB_FLAGS_SOCKET_CANT_READ;
		SCTP_INP_READ_UNLOCK(inp);
		SCTP_INP_WUNLOCK(inp);
		so->so_rcv.sb_cc = 0;
		so->so_rcv.sb_mbcnt = 0;
		so->so_rcv.sb_mb = NULL;
	}
	if ((how == PRU_FLUSH_WR) || (how == PRU_FLUSH_RDWR)) {
		/*
		 * First make sure the sb will be happy, we don't use these
		 * except maybe the count
		 */
		so->so_snd.sb_cc = 0;
		so->so_snd.sb_mbcnt = 0;
		so->so_snd.sb_mb = NULL;

	}
	return (0);
}