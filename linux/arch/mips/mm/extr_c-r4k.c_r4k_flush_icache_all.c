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
 scalar_t__ cpu_has_vtag_icache ; 
 int /*<<< orphan*/  r4k_blast_icache () ; 

__attribute__((used)) static void r4k_flush_icache_all(void)
{
	if (cpu_has_vtag_icache)
		r4k_blast_icache();
}