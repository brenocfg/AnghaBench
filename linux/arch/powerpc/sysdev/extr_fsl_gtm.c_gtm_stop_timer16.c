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
struct gtm_timer {int /*<<< orphan*/  gtevr; int /*<<< orphan*/  gtcfr; struct gtm* gtm; } ;
struct gtm {int /*<<< orphan*/  lock; struct gtm_timer* timers; } ;

/* Variables and functions */
 int /*<<< orphan*/  GTCFR_STP (int) ; 
 int /*<<< orphan*/  out_be16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setbits8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void gtm_stop_timer16(struct gtm_timer *tmr)
{
	struct gtm *gtm = tmr->gtm;
	int num = tmr - &gtm->timers[0];
	unsigned long flags;

	spin_lock_irqsave(&gtm->lock, flags);

	setbits8(tmr->gtcfr, GTCFR_STP(num));
	out_be16(tmr->gtevr, 0xFFFF);

	spin_unlock_irqrestore(&gtm->lock, flags);
}