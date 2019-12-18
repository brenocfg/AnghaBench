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
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  callout_schedule (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ofw_cngetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_timer ; 
 int /*<<< orphan*/  polltime ; 
 int /*<<< orphan*/  tty_lock_assert (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttydisc_rint (struct tty*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttydisc_rint_done (struct tty*) ; 

__attribute__((used)) static void
ofw_timeout(void *v)
{
	struct	tty *tp;
	int 	c;

	tp = (struct tty *)v;

	tty_lock_assert(tp, MA_OWNED);
	while ((c = ofw_cngetc(NULL)) != -1)
		ttydisc_rint(tp, c, 0);
	ttydisc_rint_done(tp);

	callout_schedule(&ofw_timer, polltime);
}