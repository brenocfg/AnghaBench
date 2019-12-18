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
uart_mvebu_divisor(int rclk, int baudrate)
{
	int divisor;

	if (baudrate == 0)
		return (0);

	divisor = (rclk >> 4) / baudrate;
	if (divisor <= 1 || divisor >= 1024)
		return (0);

	return (divisor);
}