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
typedef  int u_long ;
struct thread {int dummy; } ;
struct cdev {int dummy; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  sc_sigio; int /*<<< orphan*/  sc_state; } ;

/* Variables and functions */
 int ENOTTY ; 
#define  FIOASYNC 134 
#define  FIOGETOWN 133 
#define  FIONBIO 132 
#define  FIONREAD 131 
#define  FIOSETOWN 130 
 int /*<<< orphan*/  LOG_ASYNC ; 
#define  TIOCGPGRP 129 
#define  TIOCSPGRP 128 
 int fgetown (int /*<<< orphan*/ *) ; 
 int fsetown (int,int /*<<< orphan*/ *) ; 
 TYPE_1__ logsoftc ; 
 int msgbuf_getcount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgbuf_lock ; 
 int /*<<< orphan*/  msgbufp ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static	int
logioctl(struct cdev *dev, u_long com, caddr_t data, int flag, struct thread *td)
{

	switch (com) {

	/* return number of characters immediately available */
	case FIONREAD:
		*(int *)data = msgbuf_getcount(msgbufp);
		break;

	case FIONBIO:
		break;

	case FIOASYNC:
		mtx_lock(&msgbuf_lock);
		if (*(int *)data)
			logsoftc.sc_state |= LOG_ASYNC;
		else
			logsoftc.sc_state &= ~LOG_ASYNC;
		mtx_unlock(&msgbuf_lock);
		break;

	case FIOSETOWN:
		return (fsetown(*(int *)data, &logsoftc.sc_sigio));

	case FIOGETOWN:
		*(int *)data = fgetown(&logsoftc.sc_sigio);
		break;

	/* This is deprecated, FIOSETOWN should be used instead. */
	case TIOCSPGRP:
		return (fsetown(-(*(int *)data), &logsoftc.sc_sigio));

	/* This is deprecated, FIOGETOWN should be used instead */
	case TIOCGPGRP:
		*(int *)data = -fgetown(&logsoftc.sc_sigio);
		break;

	default:
		return (ENOTTY);
	}
	return (0);
}