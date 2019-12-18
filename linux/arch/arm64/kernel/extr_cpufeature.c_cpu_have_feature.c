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
 int BIT (unsigned int) ; 
 unsigned int MAX_CPU_FEATURES ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int elf_hwcap ; 

bool cpu_have_feature(unsigned int num)
{
	WARN_ON(num >= MAX_CPU_FEATURES);
	return elf_hwcap & BIT(num);
}