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
 int /*<<< orphan*/  IMCR_L1DWBAR ; 
 int /*<<< orphan*/  IMCR_L1DWWC ; 
 int /*<<< orphan*/  cache_block_operation (unsigned int*,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void L1D_cache_block_writeback(unsigned int start, unsigned int end)
{
	cache_block_operation((unsigned int *) start,
			      (unsigned int *) end,
			      IMCR_L1DWBAR, IMCR_L1DWWC);
}