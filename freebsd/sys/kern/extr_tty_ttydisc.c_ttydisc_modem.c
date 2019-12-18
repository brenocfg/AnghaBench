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
struct tty {int /*<<< orphan*/  t_flags; int /*<<< orphan*/  t_dcdwait; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCAL ; 
 scalar_t__ CMP_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  TF_ZOMBIE ; 
 int /*<<< orphan*/  c ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flush (struct tty*,int) ; 
 int /*<<< orphan*/  tty_lock_assert (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_opened (struct tty*) ; 
 int /*<<< orphan*/  tty_signal_sessleader (struct tty*,int /*<<< orphan*/ ) ; 

void
ttydisc_modem(struct tty *tp, int open)
{

	tty_lock_assert(tp, MA_OWNED);

	if (open)
		cv_broadcast(&tp->t_dcdwait);

	/*
	 * Ignore modem status lines when CLOCAL is turned on, but don't
	 * enter the zombie state when the TTY isn't opened, because
	 * that would cause the TTY to be in zombie state after being
	 * opened.
	 */
	if (!tty_opened(tp) || CMP_FLAG(c, CLOCAL))
		return;

	if (open == 0) {
		/*
		 * Lost carrier.
		 */
		tp->t_flags |= TF_ZOMBIE;

		tty_signal_sessleader(tp, SIGHUP);
		tty_flush(tp, FREAD|FWRITE);
	} else {
		/*
		 * Carrier is back again.
		 */

		/* XXX: what should we do here? */
	}
}