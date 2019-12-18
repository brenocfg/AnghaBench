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
struct tty {int dummy; } ;
struct terminal {struct tty* tm_tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  ttydisc_rint_done (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_rint_simple (struct tty*,void const*,size_t) ; 

__attribute__((used)) static void
termteken_respond(void *softc, const void *buf, size_t len)
{
#if 0
	struct terminal *tm = softc;
	struct tty *tp;

	/*
	 * Only inject a response into the TTY if the data actually
	 * originated from the TTY.
	 *
	 * XXX: This cannot be done right now.  The TTY could pick up
	 * other locks.  It could also in theory cause loops, when the
	 * TTY performs echoing of a command that generates even more
	 * input.
	 */
	tp = tm->tm_tty;
	if (tp == NULL)
		return;

	ttydisc_rint_simple(tp, buf, len);
	ttydisc_rint_done(tp);
#endif
}