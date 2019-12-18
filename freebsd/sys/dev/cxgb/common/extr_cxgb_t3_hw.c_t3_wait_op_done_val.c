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
typedef  int u32 ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int EAGAIN ; 
 int t3_read_reg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int t3_wait_op_done_val(adapter_t *adapter, int reg, u32 mask, int polarity,
			int attempts, int delay, u32 *valp)
{
	while (1) {
		u32 val = t3_read_reg(adapter, reg);

		if (!!(val & mask) == polarity) {
			if (valp)
				*valp = val;
			return 0;
		}
		if (--attempts == 0)
			return -EAGAIN;
		if (delay)
			udelay(delay);
	}
}