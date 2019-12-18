#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  dump_active; } ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t EPERM ; 
 int /*<<< orphan*/  fadump_invalidate_release_mem () ; 
 TYPE_1__ fw_dump ; 
 scalar_t__ kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  vmcore_cleanup () ; 

__attribute__((used)) static ssize_t fadump_release_memory_store(struct kobject *kobj,
					struct kobj_attribute *attr,
					const char *buf, size_t count)
{
	int input = -1;

	if (!fw_dump.dump_active)
		return -EPERM;

	if (kstrtoint(buf, 0, &input))
		return -EINVAL;

	if (input == 1) {
		/*
		 * Take away the '/proc/vmcore'. We are releasing the dump
		 * memory, hence it will not be valid anymore.
		 */
#ifdef CONFIG_PROC_VMCORE
		vmcore_cleanup();
#endif
		fadump_invalidate_release_mem();

	} else
		return -EINVAL;
	return count;
}