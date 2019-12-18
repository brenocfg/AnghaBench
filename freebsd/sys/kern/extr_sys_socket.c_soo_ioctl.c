#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct TYPE_10__ {int sb_state; int /*<<< orphan*/  sb_mbcnt; int /*<<< orphan*/  sb_mbmax; int /*<<< orphan*/  sb_hiwat; int /*<<< orphan*/  sb_flags; } ;
struct socket {TYPE_2__* so_proto; int /*<<< orphan*/  so_vnet; int /*<<< orphan*/  so_fibnum; TYPE_3__ so_rcv; int /*<<< orphan*/  so_sigio; TYPE_3__ so_snd; int /*<<< orphan*/  sol_sbsnd_flags; int /*<<< orphan*/  sol_sbrcv_flags; int /*<<< orphan*/  so_state; } ;
struct file {struct socket* f_data; } ;
struct TYPE_9__ {TYPE_1__* pr_usrreqs; } ;
struct TYPE_8__ {int (* pru_control ) (struct socket*,int,void*,int /*<<< orphan*/ ,struct thread*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
#define  FIOASYNC 137 
#define  FIOGETOWN 136 
#define  FIONBIO 135 
#define  FIONREAD 134 
#define  FIONSPACE 133 
#define  FIONWRITE 132 
#define  FIOSETOWN 131 
 char IOCGROUP (int) ; 
 int SBS_RCVATMARK ; 
 int /*<<< orphan*/  SB_ASYNC ; 
#define  SIOCATMARK 130 
#define  SIOCGPGRP 129 
#define  SIOCSPGRP 128 
 int /*<<< orphan*/  SOCKBUF_LOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int /*<<< orphan*/  SOCK_UNLOCK (struct socket*) ; 
 int /*<<< orphan*/  SOLISTENING (struct socket*) ; 
 int /*<<< orphan*/  SS_ASYNC ; 
 int /*<<< orphan*/  SS_NBIO ; 
 int fgetown (int /*<<< orphan*/ *) ; 
 int fsetown (int,int /*<<< orphan*/ *) ; 
 int ifioctl (struct socket*,int,void*,struct thread*) ; 
 int rtioctl_fib (int,void*,int /*<<< orphan*/ ) ; 
 int sbavail (TYPE_3__*) ; 
 int sbspace (TYPE_3__*) ; 
 int /*<<< orphan*/  sbused (TYPE_3__*) ; 
 int stub1 (struct socket*,int,void*,int /*<<< orphan*/ ,struct thread*) ; 

__attribute__((used)) static int
soo_ioctl(struct file *fp, u_long cmd, void *data, struct ucred *active_cred,
    struct thread *td)
{
	struct socket *so = fp->f_data;
	int error = 0;

	switch (cmd) {
	case FIONBIO:
		SOCK_LOCK(so);
		if (*(int *)data)
			so->so_state |= SS_NBIO;
		else
			so->so_state &= ~SS_NBIO;
		SOCK_UNLOCK(so);
		break;

	case FIOASYNC:
		if (*(int *)data) {
			SOCK_LOCK(so);
			so->so_state |= SS_ASYNC;
			if (SOLISTENING(so)) {
				so->sol_sbrcv_flags |= SB_ASYNC;
				so->sol_sbsnd_flags |= SB_ASYNC;
			} else {
				SOCKBUF_LOCK(&so->so_rcv);
				so->so_rcv.sb_flags |= SB_ASYNC;
				SOCKBUF_UNLOCK(&so->so_rcv);
				SOCKBUF_LOCK(&so->so_snd);
				so->so_snd.sb_flags |= SB_ASYNC;
				SOCKBUF_UNLOCK(&so->so_snd);
			}
			SOCK_UNLOCK(so);
		} else {
			SOCK_LOCK(so);
			so->so_state &= ~SS_ASYNC;
			if (SOLISTENING(so)) {
				so->sol_sbrcv_flags &= ~SB_ASYNC;
				so->sol_sbsnd_flags &= ~SB_ASYNC;
			} else {
				SOCKBUF_LOCK(&so->so_rcv);
				so->so_rcv.sb_flags &= ~SB_ASYNC;
				SOCKBUF_UNLOCK(&so->so_rcv);
				SOCKBUF_LOCK(&so->so_snd);
				so->so_snd.sb_flags &= ~SB_ASYNC;
				SOCKBUF_UNLOCK(&so->so_snd);
			}
			SOCK_UNLOCK(so);
		}
		break;

	case FIONREAD:
		/* Unlocked read. */
		*(int *)data = sbavail(&so->so_rcv);
		break;

	case FIONWRITE:
		/* Unlocked read. */
		*(int *)data = sbavail(&so->so_snd);
		break;

	case FIONSPACE:
		/* Unlocked read. */
		if ((so->so_snd.sb_hiwat < sbused(&so->so_snd)) ||
		    (so->so_snd.sb_mbmax < so->so_snd.sb_mbcnt))
			*(int *)data = 0;
		else
			*(int *)data = sbspace(&so->so_snd);
		break;

	case FIOSETOWN:
		error = fsetown(*(int *)data, &so->so_sigio);
		break;

	case FIOGETOWN:
		*(int *)data = fgetown(&so->so_sigio);
		break;

	case SIOCSPGRP:
		error = fsetown(-(*(int *)data), &so->so_sigio);
		break;

	case SIOCGPGRP:
		*(int *)data = -fgetown(&so->so_sigio);
		break;

	case SIOCATMARK:
		/* Unlocked read. */
		*(int *)data = (so->so_rcv.sb_state & SBS_RCVATMARK) != 0;
		break;
	default:
		/*
		 * Interface/routing/protocol specific ioctls: interface and
		 * routing ioctls should have a different entry since a
		 * socket is unnecessary.
		 */
		if (IOCGROUP(cmd) == 'i')
			error = ifioctl(so, cmd, data, td);
		else if (IOCGROUP(cmd) == 'r') {
			CURVNET_SET(so->so_vnet);
			error = rtioctl_fib(cmd, data, so->so_fibnum);
			CURVNET_RESTORE();
		} else {
			CURVNET_SET(so->so_vnet);
			error = ((*so->so_proto->pr_usrreqs->pru_control)
			    (so, cmd, data, 0, td));
			CURVNET_RESTORE();
		}
		break;
	}
	return (error);
}