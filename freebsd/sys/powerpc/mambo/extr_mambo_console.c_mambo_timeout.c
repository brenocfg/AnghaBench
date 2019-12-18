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
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mambo_callout ; 
 int mambo_cngetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  polltime ; 
 int /*<<< orphan*/  tp ; 
 int /*<<< orphan*/  tty_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttydisc_rint (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttydisc_rint_done (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mambo_timeout(void *v)
{
	int 	c;

	tty_lock(tp);
	while ((c = mambo_cngetc(NULL)) != -1)
		ttydisc_rint(tp, c, 0);
	ttydisc_rint_done(tp);
	tty_unlock(tp);

	callout_reset(&mambo_callout, polltime, mambo_timeout, NULL);
}