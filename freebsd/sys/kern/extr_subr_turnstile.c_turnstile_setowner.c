#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct turnstile {struct thread* ts_owner; } ;
struct thread {int /*<<< orphan*/  td_contested; TYPE_1__* td_proc; } ;
struct TYPE_2__ {scalar_t__ p_magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct turnstile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ P_MAGIC ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  td_contested_lock ; 
 int /*<<< orphan*/  ts_link ; 

__attribute__((used)) static void
turnstile_setowner(struct turnstile *ts, struct thread *owner)
{

	mtx_assert(&td_contested_lock, MA_OWNED);
	MPASS(ts->ts_owner == NULL);

	/* A shared lock might not have an owner. */
	if (owner == NULL)
		return;

	MPASS(owner->td_proc->p_magic == P_MAGIC);
	ts->ts_owner = owner;
	LIST_INSERT_HEAD(&owner->td_contested, ts, ts_link);
}