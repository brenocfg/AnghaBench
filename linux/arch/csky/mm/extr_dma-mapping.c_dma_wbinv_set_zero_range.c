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
 int /*<<< orphan*/  dma_wbinv_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void dma_wbinv_set_zero_range(unsigned long start, unsigned long end)
{
	memset((void *)start, 0, end - start);
	dma_wbinv_range(start, end);
}