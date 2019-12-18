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
struct gtm_timer {int requested; TYPE_1__* gtm; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  gtm_stop_timer16 (struct gtm_timer*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void gtm_put_timer16(struct gtm_timer *tmr)
{
	gtm_stop_timer16(tmr);

	spin_lock_irq(&tmr->gtm->lock);
	tmr->requested = false;
	spin_unlock_irq(&tmr->gtm->lock);
}