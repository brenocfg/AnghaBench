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
typedef  int uint64_t ;
typedef  int uint16_t ;
struct vatpit {int dummy; } ;
struct channel {int olbyte; int initial; int* ol; int /*<<< orphan*/  status; int /*<<< orphan*/  now_bt; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIT_8254_FREQ ; 
 int TIMER_DIV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TIMER_STS_NULLCNT ; 
 int /*<<< orphan*/  binuptime (int /*<<< orphan*/ *) ; 
 int vatpit_delta_ticks (struct vatpit*,struct channel*) ; 

__attribute__((used)) static uint16_t
pit_update_counter(struct vatpit *vatpit, struct channel *c, bool latch)
{
	uint16_t lval;
	uint64_t delta_ticks;

	/* cannot latch a new value until the old one has been consumed */
	if (latch && c->olbyte != 0)
		return (0);

	if (c->initial == 0) {
		/*
		 * This is possibly an o/s bug - reading the value of
		 * the timer without having set up the initial value.
		 *
		 * The original user-space version of this code set
		 * the timer to 100hz in this condition; do the same
		 * here.
		 */
		c->initial = TIMER_DIV(PIT_8254_FREQ, 100);
		binuptime(&c->now_bt);
		c->status &= ~TIMER_STS_NULLCNT;
	}

	delta_ticks = vatpit_delta_ticks(vatpit, c);
	lval = c->initial - delta_ticks % c->initial;

	if (latch) {
		c->olbyte = 2;
		c->ol[1] = lval;		/* LSB */
		c->ol[0] = lval >> 8;		/* MSB */
	}

	return (lval);
}