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
struct memory_block {scalar_t__ state; scalar_t__ section_count; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MEM_OFFLINE ; 
 int /*<<< orphan*/  MEM_ONLINE ; 
 int memory_block_change_state (struct memory_block*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ sections_per_block ; 
 struct memory_block* to_memory_block (struct device*) ; 

__attribute__((used)) static int memory_subsys_offline(struct device *dev)
{
	struct memory_block *mem = to_memory_block(dev);

	if (mem->state == MEM_OFFLINE)
		return 0;

	/* Can't offline block with non-present sections */
	if (mem->section_count != sections_per_block)
		return -EINVAL;

	return memory_block_change_state(mem, MEM_OFFLINE, MEM_ONLINE);
}