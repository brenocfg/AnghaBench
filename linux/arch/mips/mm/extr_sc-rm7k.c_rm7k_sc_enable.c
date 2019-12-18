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
 int RM7K_CONF_SE ; 
 int /*<<< orphan*/  __rm7k_sc_enable ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int read_c0_config () ; 
 int /*<<< orphan*/  rm7k_tc_enable () ; 
 scalar_t__ rm7k_tcache_init ; 
 int /*<<< orphan*/  run_uncached (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rm7k_sc_enable(void)
{
	if (read_c0_config() & RM7K_CONF_SE)
		return;

	pr_info("Enabling secondary cache...\n");
	run_uncached(__rm7k_sc_enable);

	if (rm7k_tcache_init)
		rm7k_tc_enable();
}