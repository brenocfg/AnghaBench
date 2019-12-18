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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int HPET_COMPARE_VAL ; 
 int /*<<< orphan*/  HPET_T0_CFG ; 
 int /*<<< orphan*/  HPET_T0_CMP ; 
 int HPET_TN_32BIT ; 
 int HPET_TN_ENABLE ; 
 int HPET_TN_LEVEL ; 
 int HPET_TN_PERIODIC ; 
 int HPET_TN_SETVAL ; 
 int /*<<< orphan*/  hpet_lock ; 
 int hpet_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpet_start_counter () ; 
 int /*<<< orphan*/  hpet_stop_counter () ; 
 int /*<<< orphan*/  hpet_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int hpet_set_state_periodic(struct clock_event_device *evt)
{
	int cfg;

	spin_lock(&hpet_lock);

	pr_info("set clock event to periodic mode!\n");
	/* stop counter */
	hpet_stop_counter();

	/* enables the timer0 to generate a periodic interrupt */
	cfg = hpet_read(HPET_T0_CFG);
	cfg &= ~HPET_TN_LEVEL;
	cfg |= HPET_TN_ENABLE | HPET_TN_PERIODIC | HPET_TN_SETVAL |
		HPET_TN_32BIT;
	hpet_write(HPET_T0_CFG, cfg);

	/* set the comparator */
	hpet_write(HPET_T0_CMP, HPET_COMPARE_VAL);
	udelay(1);
	hpet_write(HPET_T0_CMP, HPET_COMPARE_VAL);

	/* start counter */
	hpet_start_counter();

	spin_unlock(&hpet_lock);
	return 0;
}