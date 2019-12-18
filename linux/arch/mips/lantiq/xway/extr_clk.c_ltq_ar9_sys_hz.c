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
 unsigned long CLOCK_333M ; 
 unsigned long CLOCK_393M ; 
 int ltq_cgu_r32 (int /*<<< orphan*/ ) ; 

unsigned long ltq_ar9_sys_hz(void)
{
	if (((ltq_cgu_r32(CGU_SYS) >> 3) & 0x3) == 0x2)
		return CLOCK_393M;
	return CLOCK_333M;
}