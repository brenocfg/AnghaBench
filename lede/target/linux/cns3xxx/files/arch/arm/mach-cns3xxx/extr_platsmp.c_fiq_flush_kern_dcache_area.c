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
 int /*<<< orphan*/  fiq_dma_flush_range (void*,void*) ; 

void fiq_flush_kern_dcache_area(void *addr, size_t size)
{
	fiq_dma_flush_range(addr, addr + size);
}