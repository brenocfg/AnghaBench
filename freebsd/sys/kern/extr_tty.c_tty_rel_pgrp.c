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
struct tty {scalar_t__ t_sessioncnt; struct pgrp* t_pgrp; } ;
struct pgrp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  tty_lock_assert (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 

void
tty_rel_pgrp(struct tty *tp, struct pgrp *pg)
{

	MPASS(tp->t_sessioncnt > 0);
	tty_lock_assert(tp, MA_OWNED);

	if (tp->t_pgrp == pg)
		tp->t_pgrp = NULL;

	tty_unlock(tp);
}