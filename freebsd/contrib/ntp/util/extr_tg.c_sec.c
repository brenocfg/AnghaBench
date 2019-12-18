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
 int /*<<< orphan*/  HIGH ; 
 int /*<<< orphan*/  LOW ; 
 int /*<<< orphan*/  OFF ; 
 int /*<<< orphan*/  peep (int,int,int /*<<< orphan*/ ) ; 
 int tone ; 

void sec(
	int	code		/* DATA0, DATA1, PI */
	)
{
	/*
	 * The WWV data pulse begins with 5 ms of 1000 Hz follwed by a
	 * guard time of 25 ms. The data pulse is 170, 570 or 770 ms at
	 * 100 Hz corresponding to 0, 1 or position indicator (PI),
	 * respectively. Note the 100-Hz data pulses are transmitted 6
	 * dB below the 1000-Hz sync pulses. Originally the data pulses
	 * were transmited 10 dB below the sync pulses, but the station
	 * engineers increased that to 6 dB because the Heath GC-1000
	 * WWV/H radio clock worked much better.
	 */
	peep(5, tone, HIGH);		/* send seconds tick */
	peep(25, tone, OFF);
	peep(code - 30, 100, LOW);	/* send data */
	peep(1000 - code, 100, OFF);
}