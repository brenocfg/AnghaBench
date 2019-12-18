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
 int /*<<< orphan*/  CGU_SYS ; 
 unsigned long CLOCK_288M ; 
 unsigned long CLOCK_432M ; 
 unsigned long CLOCK_500M ; 
 int ltq_cgu_r32 (int /*<<< orphan*/ ) ; 

unsigned long ltq_vr9_pp32_hz(void)
{
	unsigned int clksys = (ltq_cgu_r32(CGU_SYS) >> 16) & 0x7;
	unsigned long clk;

	switch (clksys) {
	case 0:
		clk = CLOCK_500M;
		break;
	case 1:
		clk = CLOCK_432M;
		break;
	case 2:
		clk = CLOCK_288M;
		break;
	default:
		clk = CLOCK_500M;
		break;
	}

	return clk;
}