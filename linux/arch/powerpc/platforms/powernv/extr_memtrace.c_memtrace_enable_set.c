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
typedef  int u64 ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int memory_block_size_bytes () ; 
 scalar_t__ memtrace_init_debugfs () ; 
 scalar_t__ memtrace_init_regions_runtime (int) ; 
 scalar_t__ memtrace_online () ; 
 int memtrace_size ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int memtrace_enable_set(void *data, u64 val)
{
	u64 bytes;

	/*
	 * Don't attempt to do anything if size isn't aligned to a memory
	 * block or equal to zero.
	 */
	bytes = memory_block_size_bytes();
	if (val & (bytes - 1)) {
		pr_err("Value must be aligned with 0x%llx\n", bytes);
		return -EINVAL;
	}

	/* Re-add/online previously removed/offlined memory */
	if (memtrace_size) {
		if (memtrace_online())
			return -EAGAIN;
	}

	if (!val)
		return 0;

	/* Offline and remove memory */
	if (memtrace_init_regions_runtime(val))
		return -EINVAL;

	if (memtrace_init_debugfs())
		return -EINVAL;

	memtrace_size = val;

	return 0;
}