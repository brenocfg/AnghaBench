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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct tty {int /*<<< orphan*/  t_mtxobj; int /*<<< orphan*/ * t_mtx; int /*<<< orphan*/  t_outserwait; int /*<<< orphan*/  t_dcdwait; int /*<<< orphan*/  t_bgwait; int /*<<< orphan*/  t_outwait; int /*<<< orphan*/  t_inwait; TYPE_1__ t_outpoll; TYPE_1__ t_inpoll; int /*<<< orphan*/  t_outq; int /*<<< orphan*/  t_inq; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TTY ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seldrain (TYPE_1__*) ; 
 int /*<<< orphan*/  ttydevsw_free (struct tty*) ; 
 int /*<<< orphan*/  ttyinq_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttyoutq_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tty_dealloc(void *arg)
{
	struct tty *tp = arg;

	/*
	 * ttyydev_leave() usually frees the i/o queues earlier, but it is
	 * not always called between queue allocation and here.  The queues
	 * may be allocated by ioctls on a pty control device without the
	 * corresponding pty slave device ever being open, or after it is
	 * closed.
	 */
	ttyinq_free(&tp->t_inq);
	ttyoutq_free(&tp->t_outq);
	seldrain(&tp->t_inpoll);
	seldrain(&tp->t_outpoll);
	knlist_destroy(&tp->t_inpoll.si_note);
	knlist_destroy(&tp->t_outpoll.si_note);

	cv_destroy(&tp->t_inwait);
	cv_destroy(&tp->t_outwait);
	cv_destroy(&tp->t_bgwait);
	cv_destroy(&tp->t_dcdwait);
	cv_destroy(&tp->t_outserwait);

	if (tp->t_mtx == &tp->t_mtxobj)
		mtx_destroy(&tp->t_mtxobj);
	ttydevsw_free(tp);
	free(tp, M_TTY);
}