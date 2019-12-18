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
z8530_divisor(int rclk, int baudrate)
{
	int act_baud, divisor, error;

	if (baudrate == 0)
		return (-1);

	divisor = (rclk + baudrate) / (baudrate << 1) - 2;
	if (divisor < 0 || divisor >= 65536)
		return (-1);
	act_baud = rclk / 2 / (divisor + 2);

	/* 10 times error in percent: */
	error = ((act_baud - baudrate) * 2000 / baudrate + 1) >> 1;

	/* 3.0% maximum error tolerance: */
	if (error < -30 || error > 30)
		return (-1);

	return (divisor);
}