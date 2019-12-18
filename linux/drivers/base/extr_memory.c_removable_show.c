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
struct memory_block {scalar_t__ state; scalar_t__ start_section_nr; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ MEM_ONLINE ; 
 int /*<<< orphan*/  PAGES_PER_SECTION ; 
 int is_mem_section_removable (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  present_section_nr (scalar_t__) ; 
 unsigned long section_nr_to_pfn (scalar_t__) ; 
 int sections_per_block ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct memory_block* to_memory_block (struct device*) ; 

__attribute__((used)) static ssize_t removable_show(struct device *dev, struct device_attribute *attr,
			      char *buf)
{
	struct memory_block *mem = to_memory_block(dev);
	unsigned long pfn;
	int ret = 1, i;

	if (mem->state != MEM_ONLINE)
		goto out;

	for (i = 0; i < sections_per_block; i++) {
		if (!present_section_nr(mem->start_section_nr + i))
			continue;
		pfn = section_nr_to_pfn(mem->start_section_nr + i);
		ret &= is_mem_section_removable(pfn, PAGES_PER_SECTION);
	}

out:
	return sprintf(buf, "%d\n", ret);
}