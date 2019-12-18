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
struct memory_block {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ MEM_OFFLINE ; 

bool is_memblock_offlined(struct memory_block *mem)
{
	return mem->state == MEM_OFFLINE;
}