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
struct flush_data {unsigned long addr1; unsigned long addr2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipi_invalidate_dcache_range ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,struct flush_data*,int) ; 

__attribute__((used)) static void system_invalidate_dcache_range(unsigned long start,
		unsigned long size)
{
	struct flush_data fd = {
		.addr1 = start,
		.addr2 = size,
	};
	on_each_cpu(ipi_invalidate_dcache_range, &fd, 1);
}