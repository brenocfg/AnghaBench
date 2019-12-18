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
struct uio {int uio_iovcnt; int uio_segflg; scalar_t__ uio_resid; scalar_t__ uio_offset; struct thread* uio_td; int /*<<< orphan*/  uio_rw; struct iovec* uio_iov; } ;
struct thread {scalar_t__* td_retval; int /*<<< orphan*/  td_proc; int /*<<< orphan*/  td_ucred; } ;
struct socket {int so_options; } ;
struct msghdr {int msg_iovlen; int /*<<< orphan*/ * msg_name; struct iovec* msg_iov; } ;
struct mbuf {int dummy; } ;
struct iovec {scalar_t__ iov_len; } ;
struct file {scalar_t__ f_data; } ;
typedef  scalar_t__ ssize_t ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  AUDIT_ARG_FD (int) ; 
 int /*<<< orphan*/  AUDIT_ARG_SOCKADDR (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int EINTR ; 
 int EINVAL ; 
 int EPIPE ; 
 int ERESTART ; 
 int EWOULDBLOCK ; 
 scalar_t__ KTRPOINT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_GENIO ; 
 int /*<<< orphan*/  KTR_STRUCT ; 
 int MSG_NOSIGNAL ; 
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int SO_NOSIGPIPE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int /*<<< orphan*/  cap_send_connect_rights ; 
 int /*<<< orphan*/  cap_send_rights ; 
 struct uio* cloneuio (struct uio*) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int getsock_cap (struct thread*,int,int /*<<< orphan*/ *,struct file**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktrgenio (int,int /*<<< orphan*/ ,struct uio*,int) ; 
 int /*<<< orphan*/  ktrsockaddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int mac_socket_check_connect (int /*<<< orphan*/ ,struct socket*,int /*<<< orphan*/ *) ; 
 int mac_socket_check_send (int /*<<< orphan*/ ,struct socket*) ; 
 int sosend (struct socket*,int /*<<< orphan*/ *,struct uio*,int /*<<< orphan*/ ,struct mbuf*,int,struct thread*) ; 
 int /*<<< orphan*/  tdsignal (struct thread*,int /*<<< orphan*/ ) ; 

int
kern_sendit(struct thread *td, int s, struct msghdr *mp, int flags,
    struct mbuf *control, enum uio_seg segflg)
{
	struct file *fp;
	struct uio auio;
	struct iovec *iov;
	struct socket *so;
	cap_rights_t *rights;
#ifdef KTRACE
	struct uio *ktruio = NULL;
#endif
	ssize_t len;
	int i, error;

	AUDIT_ARG_FD(s);
	rights = &cap_send_rights;
	if (mp->msg_name != NULL) {
		AUDIT_ARG_SOCKADDR(td, AT_FDCWD, mp->msg_name);
		rights = &cap_send_connect_rights;
	}
	error = getsock_cap(td, s, rights, &fp, NULL, NULL);
	if (error != 0) {
		m_freem(control);
		return (error);
	}
	so = (struct socket *)fp->f_data;

#ifdef KTRACE
	if (mp->msg_name != NULL && KTRPOINT(td, KTR_STRUCT))
		ktrsockaddr(mp->msg_name);
#endif
#ifdef MAC
	if (mp->msg_name != NULL) {
		error = mac_socket_check_connect(td->td_ucred, so,
		    mp->msg_name);
		if (error != 0) {
			m_freem(control);
			goto bad;
		}
	}
	error = mac_socket_check_send(td->td_ucred, so);
	if (error != 0) {
		m_freem(control);
		goto bad;
	}
#endif

	auio.uio_iov = mp->msg_iov;
	auio.uio_iovcnt = mp->msg_iovlen;
	auio.uio_segflg = segflg;
	auio.uio_rw = UIO_WRITE;
	auio.uio_td = td;
	auio.uio_offset = 0;			/* XXX */
	auio.uio_resid = 0;
	iov = mp->msg_iov;
	for (i = 0; i < mp->msg_iovlen; i++, iov++) {
		if ((auio.uio_resid += iov->iov_len) < 0) {
			error = EINVAL;
			m_freem(control);
			goto bad;
		}
	}
#ifdef KTRACE
	if (KTRPOINT(td, KTR_GENIO))
		ktruio = cloneuio(&auio);
#endif
	len = auio.uio_resid;
	error = sosend(so, mp->msg_name, &auio, 0, control, flags, td);
	if (error != 0) {
		if (auio.uio_resid != len && (error == ERESTART ||
		    error == EINTR || error == EWOULDBLOCK))
			error = 0;
		/* Generation of SIGPIPE can be controlled per socket */
		if (error == EPIPE && !(so->so_options & SO_NOSIGPIPE) &&
		    !(flags & MSG_NOSIGNAL)) {
			PROC_LOCK(td->td_proc);
			tdsignal(td, SIGPIPE);
			PROC_UNLOCK(td->td_proc);
		}
	}
	if (error == 0)
		td->td_retval[0] = len - auio.uio_resid;
#ifdef KTRACE
	if (ktruio != NULL) {
		ktruio->uio_resid = td->td_retval[0];
		ktrgenio(s, UIO_WRITE, ktruio, error);
	}
#endif
bad:
	fdrop(fp, td);
	return (error);
}