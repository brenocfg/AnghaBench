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
 int /*<<< orphan*/  CONFIG_KASAN ; 
 int /*<<< orphan*/  DIAG_STAT_X308 ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __arch_local_irq_stosm (int) ; 
 int __diag308 (unsigned long,void*) ; 
 int /*<<< orphan*/  diag_stat_inc (int /*<<< orphan*/ ) ; 

int diag308(unsigned long subcode, void *addr)
{
	if (IS_ENABLED(CONFIG_KASAN))
		__arch_local_irq_stosm(0x04); /* enable DAT */
	diag_stat_inc(DIAG_STAT_X308);
	return __diag308(subcode, addr);
}