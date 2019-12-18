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
 unsigned long CKSEG0ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Page_Invalidate_T ; 
 int /*<<< orphan*/  cache_op (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ tc_pagesize ; 
 unsigned long tcache_size ; 
 int /*<<< orphan*/  write_c0_taglo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void blast_rm7k_tcache(void)
{
	unsigned long start = CKSEG0ADDR(0);
	unsigned long end = start + tcache_size;

	write_c0_taglo(0);

	while (start < end) {
		cache_op(Page_Invalidate_T, start);
		start += tc_pagesize;
	}
}