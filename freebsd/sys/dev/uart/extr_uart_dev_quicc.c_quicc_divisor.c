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
quicc_divisor(int rclk, int baudrate)
{
	int act_baud, divisor, error;

	if (baudrate == 0)
		return (-1);

	divisor = rclk / baudrate / 16;
	if (divisor > 4096)
		divisor = ((divisor >> 3) - 2) | 1;
	else if (divisor >= 0)
		divisor = (divisor - 1) << 1;
	if (divisor < 0 || divisor >= 8192)
		return (-1);
	act_baud = rclk / (((divisor >> 1) + 1) << ((divisor & 1) ? 8 : 4));

	/* 10 times error in percent: */
	error = ((act_baud - baudrate) * 2000 / baudrate + 1) >> 1;

	/* 3.0% maximum error tolerance: */
	if (error < -30 || error > 30)
		return (-1);

	return (divisor);
}