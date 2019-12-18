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
struct socfpga_fpga_priv {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  msleep (int) ; 
 int socfpga_fpga_state_get (struct socfpga_fpga_priv*) ; 

__attribute__((used)) static int socfpga_fpga_wait_for_state(struct socfpga_fpga_priv *priv,
				       u32 state)
{
	int timeout = 2;

	/*
	 * HW doesn't support an interrupt for changes in state, so poll to see
	 * if it matches the requested state within the timeout period.
	 */
	do {
		if ((socfpga_fpga_state_get(priv) & state) != 0)
			return 0;
		msleep(20);
	} while (timeout--);

	return -ETIMEDOUT;
}