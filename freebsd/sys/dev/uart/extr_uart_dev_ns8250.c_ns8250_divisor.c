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
 int UART_DEV_TOLERANCE_PCT ; 

__attribute__((used)) static int
ns8250_divisor(int rclk, int baudrate)
{
	int actual_baud, divisor;
	int error;

	if (baudrate == 0)
		return (0);

	divisor = (rclk / (baudrate << 3) + 1) >> 1;
	if (divisor == 0 || divisor >= 65536)
		return (0);
	actual_baud = rclk / (divisor << 4);

	/* 10 times error in percent: */
	error = ((actual_baud - baudrate) * 2000 / baudrate + 1) >> 1;

	/* enforce maximum error tolerance: */
	if (error < -UART_DEV_TOLERANCE_PCT || error > UART_DEV_TOLERANCE_PCT)
		return (0);

	return (divisor);
}