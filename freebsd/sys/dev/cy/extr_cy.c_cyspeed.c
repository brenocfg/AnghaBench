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
typedef  int u_long ;
typedef  int speed_t ;

/* Variables and functions */

__attribute__((used)) static int
cyspeed(speed_t speed, u_long cy_clock, int *prescaler_io)
{
	int	actual;
	int	error;
	int	divider;
	int	prescaler;
	int	prescaler_unit;

	if (speed == 0)
		return (0);
	if (speed < 0 || speed > 150000)
		return (-1);

	/* determine which prescaler to use */
	for (prescaler_unit = 4, prescaler = 2048; prescaler_unit;
		prescaler_unit--, prescaler >>= 2) {
		if (cy_clock / prescaler / speed > 63)
			break;
	}

	divider = (cy_clock / prescaler * 2 / speed + 1) / 2; /* round off */
	if (divider > 255)
		divider = 255;
	actual = cy_clock/prescaler/divider;

	/* 10 times error in percent: */
	error = ((actual - (long)speed) * 2000 / (long)speed + 1) / 2;

	/* 3.0% max error tolerance */
	if (error < -30 || error > 30)
		return (-1);

	*prescaler_io = prescaler_unit;
	return (divider);
}