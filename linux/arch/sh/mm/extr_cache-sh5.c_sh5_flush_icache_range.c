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
struct flusher_data {unsigned long addr1; unsigned long addr2; } ;

/* Variables and functions */
 int /*<<< orphan*/  __flush_purge_region (void*,unsigned long) ; 
 int /*<<< orphan*/  sh64_icache_inv_kernel_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void sh5_flush_icache_range(void *args)
{
	struct flusher_data *data = args;
	unsigned long start, end;

	start = data->addr1;
	end = data->addr2;

	__flush_purge_region((void *)start, end);
	wmb();
	sh64_icache_inv_kernel_range(start, end);
}