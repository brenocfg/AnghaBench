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

/* Variables and functions */
 int /*<<< orphan*/  GC_LOCK () ; 
 int /*<<< orphan*/  GC_UNLOCK () ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct tty*) ; 
 int /*<<< orphan*/  gxemul_cons_alt_break_state ; 
 int /*<<< orphan*/  gxemul_cons_callout ; 
 int /*<<< orphan*/  gxemul_cons_polltime ; 
 int gxemul_cons_read () ; 
 scalar_t__ gxemul_cons_readable () ; 
 int /*<<< orphan*/  kdb_alt_break (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_rint (struct tty*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttydisc_rint_done (struct tty*) ; 

__attribute__((used)) static void
gxemul_cons_timeout(void *v)
{
	struct tty *tp;
	int c;

	tp = v;
	tty_lock(tp);
	GC_LOCK();
	while (gxemul_cons_readable()) {
		c = gxemul_cons_read();
		GC_UNLOCK();
#ifdef KDB
		kdb_alt_break(c, &gxemul_cons_alt_break_state);
#endif
		ttydisc_rint(tp, c, 0);
		GC_LOCK();
	}
	GC_UNLOCK();
	ttydisc_rint_done(tp);
	tty_unlock(tp);
	callout_reset(&gxemul_cons_callout, gxemul_cons_polltime,
	    gxemul_cons_timeout, tp);
}