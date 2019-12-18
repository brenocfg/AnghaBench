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
struct memory_block {scalar_t__ state; int online_type; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_OFFLINE ; 
 scalar_t__ MEM_ONLINE ; 
 int MMOP_ONLINE_KEEP ; 
 int memory_block_change_state (struct memory_block*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct memory_block* to_memory_block (struct device*) ; 

__attribute__((used)) static int memory_subsys_online(struct device *dev)
{
	struct memory_block *mem = to_memory_block(dev);
	int ret;

	if (mem->state == MEM_ONLINE)
		return 0;

	/*
	 * If we are called from state_store(), online_type will be
	 * set >= 0 Otherwise we were called from the device online
	 * attribute and need to set the online_type.
	 */
	if (mem->online_type < 0)
		mem->online_type = MMOP_ONLINE_KEEP;

	ret = memory_block_change_state(mem, MEM_ONLINE, MEM_OFFLINE);

	/* clear online_type */
	mem->online_type = -1;

	return ret;
}