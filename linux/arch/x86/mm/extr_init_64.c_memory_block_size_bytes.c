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
 unsigned long memory_block_size_probed ; 
 unsigned long probe_memory_block_size () ; 

unsigned long memory_block_size_bytes(void)
{
	if (!memory_block_size_probed)
		memory_block_size_probed = probe_memory_block_size();

	return memory_block_size_probed;
}