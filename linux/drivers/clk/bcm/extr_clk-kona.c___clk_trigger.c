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
struct ccu_data {int dummy; } ;
struct bcm_clk_trig {int bit; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int __ccu_wait_bit (struct ccu_data*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  __ccu_write (struct ccu_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool __clk_trigger(struct ccu_data *ccu, struct bcm_clk_trig *trig)
{
	/* Trigger the clock and wait for it to finish */
	__ccu_write(ccu, trig->offset, 1 << trig->bit);

	return __ccu_wait_bit(ccu, trig->offset, trig->bit, false);
}