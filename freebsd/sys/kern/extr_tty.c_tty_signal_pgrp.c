#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int c_lflag; } ;
struct tty {int /*<<< orphan*/ * t_pgrp; TYPE_1__ t_termios; int /*<<< orphan*/  t_flags; } ;
struct TYPE_6__ {int ksi_signo; int /*<<< orphan*/  ksi_code; } ;
typedef  TYPE_2__ ksiginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int NOKERNINFO ; 
 int NSIG ; 
 int /*<<< orphan*/  PGRP_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PGRP_UNLOCK (int /*<<< orphan*/ *) ; 
 int SIGINFO ; 
 int /*<<< orphan*/  SI_KERNEL ; 
 int /*<<< orphan*/  TF_STOPPED ; 
 int /*<<< orphan*/  ksiginfo_init (TYPE_2__*) ; 
 int /*<<< orphan*/  pgsignal (int /*<<< orphan*/ *,int,int,TYPE_2__*) ; 
 int /*<<< orphan*/  tty_info (struct tty*) ; 
 int /*<<< orphan*/  tty_lock_assert (struct tty*,int /*<<< orphan*/ ) ; 

void
tty_signal_pgrp(struct tty *tp, int sig)
{
	ksiginfo_t ksi;

	tty_lock_assert(tp, MA_OWNED);
	MPASS(sig >= 1 && sig < NSIG);

	/* Make signals start output again. */
	tp->t_flags &= ~TF_STOPPED;

	if (sig == SIGINFO && !(tp->t_termios.c_lflag & NOKERNINFO))
		tty_info(tp);
	if (tp->t_pgrp != NULL) {
		ksiginfo_init(&ksi);
		ksi.ksi_signo = sig;
		ksi.ksi_code = SI_KERNEL;
		PGRP_LOCK(tp->t_pgrp);
		pgsignal(tp->t_pgrp, sig, 1, &ksi);
		PGRP_UNLOCK(tp->t_pgrp);
	}
}