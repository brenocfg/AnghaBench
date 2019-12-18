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
struct memory_block {unsigned long state; int /*<<< orphan*/  online_type; int /*<<< orphan*/  start_section_nr; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long MEM_GOING_OFFLINE ; 
 unsigned long MEM_OFFLINE ; 
 int memory_block_action (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int memory_block_change_state(struct memory_block *mem,
		unsigned long to_state, unsigned long from_state_req)
{
	int ret = 0;

	if (mem->state != from_state_req)
		return -EINVAL;

	if (to_state == MEM_OFFLINE)
		mem->state = MEM_GOING_OFFLINE;

	ret = memory_block_action(mem->start_section_nr, to_state,
				mem->online_type);

	mem->state = ret ? from_state_req : to_state;

	return ret;
}