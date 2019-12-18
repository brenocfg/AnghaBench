#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {int /*<<< orphan*/  td_proc; int /*<<< orphan*/  td_ucred; } ;
struct TYPE_3__ {int sb_timeo; int /*<<< orphan*/  sb_flags; } ;
struct socket {int so_state; int so_error; int /*<<< orphan*/  so_timeo; TYPE_1__ so_snd; TYPE_1__ so_rcv; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct nbpcb {int /*<<< orphan*/  nbp_vc; int /*<<< orphan*/  nbp_rcvbuf; int /*<<< orphan*/  nbp_sndbuf; struct socket* nbp_tso; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  PSOCK ; 
 int SBT_1S ; 
 int /*<<< orphan*/  SB_NOINTR ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_KEEPALIVE ; 
 int /*<<< orphan*/  SO_RCV ; 
 int SS_ISCONNECTING ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int hz ; 
 int nb_intr (struct nbpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nb_setsockopt_int (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nb_upcall ; 
 int /*<<< orphan*/  smb_nbst_disconnect (int /*<<< orphan*/ ,struct thread*) ; 
 int soconnect (struct socket*,struct sockaddr*,struct thread*) ; 
 int socreate (int /*<<< orphan*/ ,struct socket**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 
 int soreserve (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soupcall_set (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nbpcb*) ; 
 int splnet () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  tsleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
nb_connect_in(struct nbpcb *nbp, struct sockaddr_in *to, struct thread *td)
{
	struct socket *so;
	int error, s;

	error = socreate(AF_INET, &so, SOCK_STREAM, IPPROTO_TCP,
	    td->td_ucred, td);
	if (error)
		return error;
	nbp->nbp_tso = so;
	SOCKBUF_LOCK(&so->so_rcv);
	soupcall_set(so, SO_RCV, nb_upcall, nbp);
	SOCKBUF_UNLOCK(&so->so_rcv);
	so->so_rcv.sb_timeo = (5 * SBT_1S);
	so->so_snd.sb_timeo = (5 * SBT_1S);
	error = soreserve(so, nbp->nbp_sndbuf, nbp->nbp_rcvbuf);
	if (error)
		goto bad;
	nb_setsockopt_int(so, SOL_SOCKET, SO_KEEPALIVE, 1);
	nb_setsockopt_int(so, IPPROTO_TCP, TCP_NODELAY, 1);
	SOCKBUF_LOCK(&so->so_rcv);
	so->so_rcv.sb_flags &= ~SB_NOINTR;
	SOCKBUF_UNLOCK(&so->so_rcv);
	SOCKBUF_LOCK(&so->so_snd);
	so->so_snd.sb_flags &= ~SB_NOINTR;
	SOCKBUF_UNLOCK(&so->so_snd);
	error = soconnect(so, (struct sockaddr*)to, td);
	if (error)
		goto bad;
	s = splnet();
	while ((so->so_state & SS_ISCONNECTING) && so->so_error == 0) {
		tsleep(&so->so_timeo, PSOCK, "nbcon", 2 * hz);
		if ((so->so_state & SS_ISCONNECTING) && so->so_error == 0 &&
			(error = nb_intr(nbp, td->td_proc)) != 0) {
			so->so_state &= ~SS_ISCONNECTING;
			splx(s);
			goto bad;
		}
	}
	if (so->so_error) {
		error = so->so_error;
		so->so_error = 0;
		splx(s);
		goto bad;
	}
	splx(s);
	return 0;
bad:
	smb_nbst_disconnect(nbp->nbp_vc, td);
	return error;
}