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
 int /*<<< orphan*/  tx39_blast_dcache () ; 
 int /*<<< orphan*/  tx39_blast_icache () ; 

__attribute__((used)) static inline void tx39___flush_cache_all(void)
{
	tx39_blast_dcache();
	tx39_blast_icache();
}