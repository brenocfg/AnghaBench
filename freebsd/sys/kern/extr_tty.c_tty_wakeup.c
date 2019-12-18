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
struct tty {int t_flags; TYPE_1__ t_inpoll; int /*<<< orphan*/  t_inwait; TYPE_1__ t_outpoll; int /*<<< orphan*/  t_outwait; int /*<<< orphan*/ * t_session; int /*<<< orphan*/ * t_sigio; } ;

/* Variables and functions */
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  KNOTE_LOCKED (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGIO ; 
 int TF_ASYNC ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgsigio (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selwakeup (TYPE_1__*) ; 

void
tty_wakeup(struct tty *tp, int flags)
{

	if (tp->t_flags & TF_ASYNC && tp->t_sigio != NULL)
		pgsigio(&tp->t_sigio, SIGIO, (tp->t_session != NULL));

	if (flags & FWRITE) {
		cv_broadcast(&tp->t_outwait);
		selwakeup(&tp->t_outpoll);
		KNOTE_LOCKED(&tp->t_outpoll.si_note, 0);
	}
	if (flags & FREAD) {
		cv_broadcast(&tp->t_inwait);
		selwakeup(&tp->t_inpoll);
		KNOTE_LOCKED(&tp->t_inpoll.si_note, 0);
	}
}