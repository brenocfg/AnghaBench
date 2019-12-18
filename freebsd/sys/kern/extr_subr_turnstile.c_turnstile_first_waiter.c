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
struct turnstile {int /*<<< orphan*/ * ts_blocked; } ;
struct thread {scalar_t__ td_priority; } ;

/* Variables and functions */
 struct thread* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 size_t TS_EXCLUSIVE_QUEUE ; 
 size_t TS_SHARED_QUEUE ; 

__attribute__((used)) static struct thread *
turnstile_first_waiter(struct turnstile *ts)
{
	struct thread *std, *xtd;

	std = TAILQ_FIRST(&ts->ts_blocked[TS_SHARED_QUEUE]);
	xtd = TAILQ_FIRST(&ts->ts_blocked[TS_EXCLUSIVE_QUEUE]);
	if (xtd == NULL || (std != NULL && std->td_priority < xtd->td_priority))
		return (std);
	return (xtd);
}