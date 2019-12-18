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

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conscallout ; 
 int /*<<< orphan*/  consmsgbuf ; 
 int /*<<< orphan*/ * constty ; 
 int /*<<< orphan*/  constty_clear () ; 
 int constty_wakeups_per_second ; 
 int hz ; 
 int msgbuf_getchar (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ tty_putchar (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tty_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
constty_timeout(void *arg)
{
	int c;

	if (constty != NULL) {
		tty_lock(constty);
		while ((c = msgbuf_getchar(&consmsgbuf)) != -1) {
			if (tty_putchar(constty, c) < 0) {
				tty_unlock(constty);
				constty = NULL;
				break;
			}
		}

		if (constty != NULL)
			tty_unlock(constty);
	}
	if (constty != NULL) {
		callout_reset(&conscallout, hz / constty_wakeups_per_second,
		    constty_timeout, NULL);
	} else {
		/* Deallocate the constty buffer memory. */
		constty_clear();
	}
}