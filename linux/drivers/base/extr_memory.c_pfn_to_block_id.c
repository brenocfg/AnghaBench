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
 unsigned long base_memory_block_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_to_section_nr (unsigned long) ; 

__attribute__((used)) static inline unsigned long pfn_to_block_id(unsigned long pfn)
{
	return base_memory_block_id(pfn_to_section_nr(pfn));
}