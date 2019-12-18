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
struct drbd_thread {scalar_t__ t_state; int /*<<< orphan*/  stop; int /*<<< orphan*/  t_lock; int /*<<< orphan*/ * task; } ;
typedef  enum drbd_thread_state { ____Placeholder_drbd_thread_state } drbd_thread_state ;

/* Variables and functions */
 int /*<<< orphan*/  DRBD_SIGKILL ; 
 int EXITING ; 
 scalar_t__ NONE ; 
 int RESTARTING ; 
 int /*<<< orphan*/ * current ; 
 int /*<<< orphan*/  drbd_thread_start (struct drbd_thread*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void _drbd_thread_stop(struct drbd_thread *thi, int restart, int wait)
{
	unsigned long flags;

	enum drbd_thread_state ns = restart ? RESTARTING : EXITING;

	/* may be called from state engine, holding the req lock irqsave */
	spin_lock_irqsave(&thi->t_lock, flags);

	if (thi->t_state == NONE) {
		spin_unlock_irqrestore(&thi->t_lock, flags);
		if (restart)
			drbd_thread_start(thi);
		return;
	}

	if (thi->t_state != ns) {
		if (thi->task == NULL) {
			spin_unlock_irqrestore(&thi->t_lock, flags);
			return;
		}

		thi->t_state = ns;
		smp_mb();
		init_completion(&thi->stop);
		if (thi->task != current)
			send_sig(DRBD_SIGKILL, thi->task, 1);
	}

	spin_unlock_irqrestore(&thi->t_lock, flags);

	if (wait)
		wait_for_completion(&thi->stop);
}