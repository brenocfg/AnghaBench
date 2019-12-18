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
 int /*<<< orphan*/  FREAD ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  rint_done ; 
 int /*<<< orphan*/  tty_lock_assert (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttydevsw_outwakeup (struct tty*) ; 
 scalar_t__ ttyhook_hashook (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttyhook_rint_done (struct tty*) ; 

void
ttydisc_rint_done(struct tty *tp)
{

	tty_lock_assert(tp, MA_OWNED);

	if (ttyhook_hashook(tp, rint_done))
		ttyhook_rint_done(tp);

	/* Wake up readers. */
	tty_wakeup(tp, FREAD);
	/* Wake up driver for echo. */
	ttydevsw_outwakeup(tp);
}