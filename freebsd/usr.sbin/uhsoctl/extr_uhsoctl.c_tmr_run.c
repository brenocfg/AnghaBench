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
struct timers {scalar_t__ res; int /*<<< orphan*/  head; } ;
struct timer_entry {scalar_t__ timeout; int /*<<< orphan*/  arg; int /*<<< orphan*/  id; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct timer_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct timer_entry* TAILQ_NEXT (struct timer_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct timer_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct timer_entry*) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tmr_run(struct timers *tmrs)
{
	struct timer_entry *te, *te2;

	te = TAILQ_FIRST(&tmrs->head);
	if (te == NULL)
		return;

	te->timeout -= tmrs->res;
	while (te->timeout <= 0) {
		te2 = TAILQ_NEXT(te, next);
		TAILQ_REMOVE(&tmrs->head, te, next);
		te->func(te->id, te->arg);
		free(te);
		te = te2;
		if (te == NULL)
			break;
	}
}