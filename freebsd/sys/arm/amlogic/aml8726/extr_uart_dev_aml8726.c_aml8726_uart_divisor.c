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

/* Variables and functions */

__attribute__((used)) static int
aml8726_uart_divisor(int rclk, int baudrate)
{
	int actual_baud, divisor;
	int error;

	if (baudrate == 0)
		return (0);

	/* integer version of (rclk / baudrate + .5) */
	divisor = ((rclk << 1) + baudrate) / (baudrate << 1);
	if (divisor == 0)
		return (0);
	actual_baud = rclk / divisor;

	/* 10 times error in percent: */
	error = (((actual_baud - baudrate) * 2000) / baudrate + 1) >> 1;

	/* 3.0% maximum error tolerance: */
	if (error < -30 || error > 30)
		return (0);

	return (divisor);
}