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
struct bcm2835_cprman {int /*<<< orphan*/  dev; } ;
struct bcm2835_clock_data {int /*<<< orphan*/  ctl_reg; } ;
struct bcm2835_clock {int /*<<< orphan*/  hw; struct bcm2835_clock_data* data; struct bcm2835_cprman* cprman; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int CM_BUSY ; 
 int /*<<< orphan*/  LOCK_TIMEOUT_NS ; 
 int /*<<< orphan*/  clk_hw_get_name (int /*<<< orphan*/ *) ; 
 int cprman_read (struct bcm2835_cprman*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 

__attribute__((used)) static void bcm2835_clock_wait_busy(struct bcm2835_clock *clock)
{
	struct bcm2835_cprman *cprman = clock->cprman;
	const struct bcm2835_clock_data *data = clock->data;
	ktime_t timeout = ktime_add_ns(ktime_get(), LOCK_TIMEOUT_NS);

	while (cprman_read(cprman, data->ctl_reg) & CM_BUSY) {
		if (ktime_after(ktime_get(), timeout)) {
			dev_err(cprman->dev, "%s: couldn't lock PLL\n",
				clk_hw_get_name(&clock->hw));
			return;
		}
		cpu_relax();
	}
}