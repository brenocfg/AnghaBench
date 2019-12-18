#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct uio {long uio_resid; } ;
struct TYPE_9__ {int /*<<< orphan*/  ru_msgsnd; } ;
struct thread {TYPE_2__ td_ru; } ;
struct TYPE_12__ {int sb_state; } ;
struct socket {scalar_t__ so_type; int so_options; int so_error; int so_state; TYPE_4__* so_proto; TYPE_5__ so_snd; } ;
struct sockaddr {int dummy; } ;
struct TYPE_8__ {long len; } ;
struct mbuf {int m_len; int m_flags; TYPE_1__ m_pkthdr; } ;
typedef  long ssize_t ;
struct TYPE_11__ {int pr_flags; TYPE_3__* pr_usrreqs; } ;
struct TYPE_10__ {int (* pru_send ) (struct socket*,int /*<<< orphan*/ ,struct mbuf*,struct sockaddr*,struct mbuf*,struct thread*) ;} ;

/* Variables and functions */
 int EDESTADDRREQ ; 
 int EFAULT ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOTCONN ; 
 int EPIPE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MSG_DONTROUTE ; 
 int MSG_EOF ; 
 int MSG_EOR ; 
 int MSG_MORETOCOME ; 
 int MSG_OOB ; 
 int M_EOR ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PRUS_EOF ; 
 int /*<<< orphan*/  PRUS_MORETOCOME ; 
 int /*<<< orphan*/  PRUS_OOB ; 
 int PR_ATOMIC ; 
 int PR_CONNREQUIRED ; 
 int PR_IMPLOPCL ; 
 int SBS_CANTSENDMORE ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (TYPE_5__*) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (TYPE_5__*) ; 
 scalar_t__ SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int /*<<< orphan*/  SOCK_UNLOCK (struct socket*) ; 
 int SO_DONTROUTE ; 
 int SS_ISCONFIRMING ; 
 int SS_ISCONNECTED ; 
 int /*<<< orphan*/  VNET_SO_ASSERT (struct socket*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_uiotombuf (struct uio*,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  max_hdr ; 
 long sbspace (TYPE_5__*) ; 
 int stub1 (struct socket*,int /*<<< orphan*/ ,struct mbuf*,struct sockaddr*,struct mbuf*,struct thread*) ; 

int
sosend_dgram(struct socket *so, struct sockaddr *addr, struct uio *uio,
    struct mbuf *top, struct mbuf *control, int flags, struct thread *td)
{
	long space;
	ssize_t resid;
	int clen = 0, error, dontroute;

	KASSERT(so->so_type == SOCK_DGRAM, ("sosend_dgram: !SOCK_DGRAM"));
	KASSERT(so->so_proto->pr_flags & PR_ATOMIC,
	    ("sosend_dgram: !PR_ATOMIC"));

	if (uio != NULL)
		resid = uio->uio_resid;
	else
		resid = top->m_pkthdr.len;
	/*
	 * In theory resid should be unsigned.  However, space must be
	 * signed, as it might be less than 0 if we over-committed, and we
	 * must use a signed comparison of space and resid.  On the other
	 * hand, a negative resid causes us to loop sending 0-length
	 * segments to the protocol.
	 */
	if (resid < 0) {
		error = EINVAL;
		goto out;
	}

	dontroute =
	    (flags & MSG_DONTROUTE) && (so->so_options & SO_DONTROUTE) == 0;
	if (td != NULL)
		td->td_ru.ru_msgsnd++;
	if (control != NULL)
		clen = control->m_len;

	SOCKBUF_LOCK(&so->so_snd);
	if (so->so_snd.sb_state & SBS_CANTSENDMORE) {
		SOCKBUF_UNLOCK(&so->so_snd);
		error = EPIPE;
		goto out;
	}
	if (so->so_error) {
		error = so->so_error;
		so->so_error = 0;
		SOCKBUF_UNLOCK(&so->so_snd);
		goto out;
	}
	if ((so->so_state & SS_ISCONNECTED) == 0) {
		/*
		 * `sendto' and `sendmsg' is allowed on a connection-based
		 * socket if it supports implied connect.  Return ENOTCONN if
		 * not connected and no address is supplied.
		 */
		if ((so->so_proto->pr_flags & PR_CONNREQUIRED) &&
		    (so->so_proto->pr_flags & PR_IMPLOPCL) == 0) {
			if ((so->so_state & SS_ISCONFIRMING) == 0 &&
			    !(resid == 0 && clen != 0)) {
				SOCKBUF_UNLOCK(&so->so_snd);
				error = ENOTCONN;
				goto out;
			}
		} else if (addr == NULL) {
			if (so->so_proto->pr_flags & PR_CONNREQUIRED)
				error = ENOTCONN;
			else
				error = EDESTADDRREQ;
			SOCKBUF_UNLOCK(&so->so_snd);
			goto out;
		}
	}

	/*
	 * Do we need MSG_OOB support in SOCK_DGRAM?  Signs here may be a
	 * problem and need fixing.
	 */
	space = sbspace(&so->so_snd);
	if (flags & MSG_OOB)
		space += 1024;
	space -= clen;
	SOCKBUF_UNLOCK(&so->so_snd);
	if (resid > space) {
		error = EMSGSIZE;
		goto out;
	}
	if (uio == NULL) {
		resid = 0;
		if (flags & MSG_EOR)
			top->m_flags |= M_EOR;
	} else {
		/*
		 * Copy the data from userland into a mbuf chain.
		 * If no data is to be copied in, a single empty mbuf
		 * is returned.
		 */
		top = m_uiotombuf(uio, M_WAITOK, space, max_hdr,
		    (M_PKTHDR | ((flags & MSG_EOR) ? M_EOR : 0)));
		if (top == NULL) {
			error = EFAULT;	/* only possible error */
			goto out;
		}
		space -= resid - uio->uio_resid;
		resid = uio->uio_resid;
	}
	KASSERT(resid == 0, ("sosend_dgram: resid != 0"));
	/*
	 * XXXRW: Frobbing SO_DONTROUTE here is even worse without sblock
	 * than with.
	 */
	if (dontroute) {
		SOCK_LOCK(so);
		so->so_options |= SO_DONTROUTE;
		SOCK_UNLOCK(so);
	}
	/*
	 * XXX all the SBS_CANTSENDMORE checks previously done could be out
	 * of date.  We could have received a reset packet in an interrupt or
	 * maybe we slept while doing page faults in uiomove() etc.  We could
	 * probably recheck again inside the locking protection here, but
	 * there are probably other places that this also happens.  We must
	 * rethink this.
	 */
	VNET_SO_ASSERT(so);
	error = (*so->so_proto->pr_usrreqs->pru_send)(so,
	    (flags & MSG_OOB) ? PRUS_OOB :
	/*
	 * If the user set MSG_EOF, the protocol understands this flag and
	 * nothing left to send then use PRU_SEND_EOF instead of PRU_SEND.
	 */
	    ((flags & MSG_EOF) &&
	     (so->so_proto->pr_flags & PR_IMPLOPCL) &&
	     (resid <= 0)) ?
		PRUS_EOF :
		/* If there is more to send set PRUS_MORETOCOME */
		(flags & MSG_MORETOCOME) ||
		(resid > 0 && space > 0) ? PRUS_MORETOCOME : 0,
		top, addr, control, td);
	if (dontroute) {
		SOCK_LOCK(so);
		so->so_options &= ~SO_DONTROUTE;
		SOCK_UNLOCK(so);
	}
	clen = 0;
	control = NULL;
	top = NULL;
out:
	if (top != NULL)
		m_freem(top);
	if (control != NULL)
		m_freem(control);
	return (error);
}