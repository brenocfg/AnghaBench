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
struct TYPE_4__ {int /*<<< orphan*/  si_note; } ;
struct TYPE_3__ {int /*<<< orphan*/  si_note; } ;
struct tty {int t_flags; int /*<<< orphan*/  t_dcdwait; TYPE_2__ t_outpoll; TYPE_1__ t_inpoll; scalar_t__ t_outlow; int /*<<< orphan*/  t_outq; scalar_t__ t_inlow; int /*<<< orphan*/  t_inq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int TF_OPENCLOSE ; 
 struct tty* constty ; 
 int /*<<< orphan*/  constty_clear () ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  knlist_clear (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tty_drain (struct tty*,int) ; 
 int /*<<< orphan*/  tty_gone (struct tty*) ; 
 int /*<<< orphan*/  tty_lock_assert (struct tty*,int /*<<< orphan*/ ) ; 
 scalar_t__ tty_opened (struct tty*) ; 
 int /*<<< orphan*/  tty_rel_free (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int /*<<< orphan*/  ttydevsw_close (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_close (struct tty*) ; 
 int /*<<< orphan*/  ttyinq_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttyoutq_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ttydev_leave(struct tty *tp)
{

	tty_lock_assert(tp, MA_OWNED);

	if (tty_opened(tp) || tp->t_flags & TF_OPENCLOSE) {
		/* Device is still opened somewhere. */
		tty_unlock(tp);
		return;
	}

	tp->t_flags |= TF_OPENCLOSE;

	/* Remove console TTY. */
	if (constty == tp)
		constty_clear();

	/* Drain any output. */
	if (!tty_gone(tp))
		tty_drain(tp, 1);

	ttydisc_close(tp);

	/* Free i/o queues now since they might be large. */
	ttyinq_free(&tp->t_inq);
	tp->t_inlow = 0;
	ttyoutq_free(&tp->t_outq);
	tp->t_outlow = 0;

	knlist_clear(&tp->t_inpoll.si_note, 1);
	knlist_clear(&tp->t_outpoll.si_note, 1);

	if (!tty_gone(tp))
		ttydevsw_close(tp);

	tp->t_flags &= ~TF_OPENCLOSE;
	cv_broadcast(&tp->t_dcdwait);
	tty_rel_free(tp);
}