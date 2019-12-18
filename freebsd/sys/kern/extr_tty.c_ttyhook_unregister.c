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
struct tty {int t_flags; int /*<<< orphan*/ * t_hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int TF_HOOK ; 
 int /*<<< orphan*/  tty_lock_assert (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_rel_free (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_optimize (struct tty*) ; 

void
ttyhook_unregister(struct tty *tp)
{

	tty_lock_assert(tp, MA_OWNED);
	MPASS(tp->t_flags & TF_HOOK);

	/* Disconnect the hook. */
	tp->t_flags &= ~TF_HOOK;
	tp->t_hook = NULL;

	/* Maybe we need to leave bypass mode. */
	ttydisc_optimize(tp);

	/* Maybe deallocate the TTY as well. */
	tty_rel_free(tp);
}