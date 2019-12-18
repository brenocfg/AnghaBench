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
typedef  unsigned long long uint64_t ;
struct pt_section {unsigned long long offset; } ;

/* Variables and functions */

uint64_t pt_section_offset(const struct pt_section *section)
{
	if (!section)
		return 0ull;

	return section->offset;
}