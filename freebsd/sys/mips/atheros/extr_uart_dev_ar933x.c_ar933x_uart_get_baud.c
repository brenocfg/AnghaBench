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
typedef  unsigned int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static unsigned long
ar933x_uart_get_baud(unsigned int clk, unsigned int scale,
    unsigned int step)
{
	uint64_t t;
	uint32_t div;

	div = (2 << 16) * (scale + 1);
	t = clk;
	t *= step;
	t += (div / 2);
	t = t / div;

	return (t);
}