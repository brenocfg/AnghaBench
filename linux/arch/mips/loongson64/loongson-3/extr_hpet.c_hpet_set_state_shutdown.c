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
 int /*<<< orphan*/  HPET_T0_CFG ; 
 int HPET_TN_ENABLE ; 
 int /*<<< orphan*/  hpet_lock ; 
 int hpet_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpet_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hpet_set_state_shutdown(struct clock_event_device *evt)
{
	int cfg;

	spin_lock(&hpet_lock);

	cfg = hpet_read(HPET_T0_CFG);
	cfg &= ~HPET_TN_ENABLE;
	hpet_write(HPET_T0_CFG, cfg);

	spin_unlock(&hpet_lock);
	return 0;
}