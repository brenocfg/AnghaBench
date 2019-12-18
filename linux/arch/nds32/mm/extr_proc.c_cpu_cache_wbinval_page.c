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
 int /*<<< orphan*/  cpu_dcache_wbinval_page (unsigned long) ; 
 int /*<<< orphan*/  cpu_icache_inval_page (unsigned long) ; 

void cpu_cache_wbinval_page(unsigned long page, int flushi)
{
	cpu_dcache_wbinval_page(page);
	if (flushi)
		cpu_icache_inval_page(page);
}