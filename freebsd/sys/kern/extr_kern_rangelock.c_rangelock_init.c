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
struct rangelock {int /*<<< orphan*/ * rl_currdep; int /*<<< orphan*/  rl_waiters; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 

void
rangelock_init(struct rangelock *lock)
{

	TAILQ_INIT(&lock->rl_waiters);
	lock->rl_currdep = NULL;
}