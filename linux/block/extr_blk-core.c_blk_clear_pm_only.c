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
struct request_queue {int /*<<< orphan*/  mq_freeze_wq; int /*<<< orphan*/  pm_only; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void blk_clear_pm_only(struct request_queue *q)
{
	int pm_only;

	pm_only = atomic_dec_return(&q->pm_only);
	WARN_ON_ONCE(pm_only < 0);
	if (pm_only == 0)
		wake_up_all(&q->mq_freeze_wq);
}