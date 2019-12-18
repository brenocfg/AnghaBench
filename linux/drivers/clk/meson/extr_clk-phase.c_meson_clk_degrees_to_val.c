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
 unsigned int DIV_ROUND_CLOSEST (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phase_step (unsigned int) ; 

__attribute__((used)) static unsigned int meson_clk_degrees_to_val(int degrees, unsigned int width)
{
	unsigned int val = DIV_ROUND_CLOSEST(degrees, phase_step(width));

	/*
	 * This last calculation is here for cases when degrees is rounded
	 * to 360, in which case val == (1 << width).
	 */
	return val % (1 << width);
}