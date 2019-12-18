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
struct tty {scalar_t__ t_sessioncnt; int /*<<< orphan*/ * t_pgrp; struct session* t_session; } ;
struct session {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  tty_rel_free (struct tty*) ; 

void
tty_rel_sess(struct tty *tp, struct session *sess)
{

	MPASS(tp->t_sessioncnt > 0);

	/* Current session has left. */
	if (tp->t_session == sess) {
		tp->t_session = NULL;
		MPASS(tp->t_pgrp == NULL);
	}
	tp->t_sessioncnt--;
	tty_rel_free(tp);
}