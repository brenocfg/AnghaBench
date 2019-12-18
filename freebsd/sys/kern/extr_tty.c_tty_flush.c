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
struct tty {int /*<<< orphan*/  t_inq; int /*<<< orphan*/  t_outq; int /*<<< orphan*/  t_flags; } ;

/* Variables and functions */
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  TF_HIWAT_OUT ; 
 int /*<<< orphan*/  TIOCPKT_FLUSHREAD ; 
 int /*<<< orphan*/  TIOCPKT_FLUSHWRITE ; 
 int /*<<< orphan*/  tty_gone (struct tty*) ; 
 int /*<<< orphan*/  tty_hiwat_in_unblock (struct tty*) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty*,int) ; 
 int /*<<< orphan*/  ttydevsw_inwakeup (struct tty*) ; 
 int /*<<< orphan*/  ttydevsw_outwakeup (struct tty*) ; 
 int /*<<< orphan*/  ttydevsw_pktnotify (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttyinq_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttyoutq_flush (int /*<<< orphan*/ *) ; 

void
tty_flush(struct tty *tp, int flags)
{

	if (flags & FWRITE) {
		tp->t_flags &= ~TF_HIWAT_OUT;
		ttyoutq_flush(&tp->t_outq);
		tty_wakeup(tp, FWRITE);
		if (!tty_gone(tp)) {
			ttydevsw_outwakeup(tp);
			ttydevsw_pktnotify(tp, TIOCPKT_FLUSHWRITE);
		}
	}
	if (flags & FREAD) {
		tty_hiwat_in_unblock(tp);
		ttyinq_flush(&tp->t_inq);
		tty_wakeup(tp, FREAD);
		if (!tty_gone(tp)) {
			ttydevsw_inwakeup(tp);
			ttydevsw_pktnotify(tp, TIOCPKT_FLUSHREAD);
		}
	}
}