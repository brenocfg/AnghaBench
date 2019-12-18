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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct pt_section {struct pt_sec_windows_mapping* mapping; } ;
struct pt_sec_windows_mapping {int /*<<< orphan*/ * end; int /*<<< orphan*/ * base; } ;

/* Variables and functions */
 int pte_internal ; 

int pt_sec_windows_memsize(const struct pt_section *section, uint64_t *size)
{
	struct pt_sec_windows_mapping *mapping;
	const uint8_t *begin, *end;

	if (!section || !size)
		return -pte_internal;

	mapping = section->mapping;
	if (!mapping)
		return -pte_internal;

	begin = mapping->base;
	end =  mapping->end;

	if (!begin || !end || end < begin)
		return -pte_internal;

	*size = (uint64_t) (end - begin);

	return 0;
}