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
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_12__ {int /*<<< orphan*/  sa_mask; scalar_t__ sa_flags; int /*<<< orphan*/  sa_handler; } ;
struct TYPE_11__ {TYPE_1__* el_signal; } ;
struct TYPE_10__ {int sig_no; TYPE_5__* sig_action; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_REFRESH ; 
#define  SIGCONT 129 
#define  SIGWINCH 128 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_ERR ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  ed_redisplay (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  el_resize (TYPE_2__*) ; 
 int errno ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  re_refresh (TYPE_2__*) ; 
 TYPE_2__* sel ; 
 int /*<<< orphan*/  sigaction (int,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int* sighdl ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  terminal__flush (TYPE_2__*) ; 
 int /*<<< orphan*/  tty_cookedmode (TYPE_2__*) ; 
 int /*<<< orphan*/  tty_rawmode (TYPE_2__*) ; 

__attribute__((used)) static void
sig_handler(int signo)
{
	int i, save_errno;
	sigset_t nset, oset;

	save_errno = errno;
	(void) sigemptyset(&nset);
	(void) sigaddset(&nset, signo);
	(void) sigprocmask(SIG_BLOCK, &nset, &oset);

	sel->el_signal->sig_no = signo;

	switch (signo) {
	case SIGCONT:
		tty_rawmode(sel);
		if (ed_redisplay(sel, 0) == CC_REFRESH)
			re_refresh(sel);
		terminal__flush(sel);
		break;

	case SIGWINCH:
		el_resize(sel);
		break;

	default:
		tty_cookedmode(sel);
		break;
	}

	for (i = 0; sighdl[i] != -1; i++)
		if (signo == sighdl[i])
			break;

	(void) sigaction(signo, &sel->el_signal->sig_action[i], NULL);
	sel->el_signal->sig_action[i].sa_handler = SIG_ERR;
	sel->el_signal->sig_action[i].sa_flags = 0;
	sigemptyset(&sel->el_signal->sig_action[i].sa_mask);
	(void) sigprocmask(SIG_SETMASK, &oset, NULL);
	(void) kill(0, signo);
	errno = save_errno;
}