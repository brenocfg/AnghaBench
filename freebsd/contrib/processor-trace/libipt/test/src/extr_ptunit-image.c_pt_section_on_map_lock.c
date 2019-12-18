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
struct pt_section {int dummy; } ;

/* Variables and functions */
 int pte_internal ; 

int pt_section_on_map_lock(struct pt_section *section)
{
	if (!section)
		return -pte_internal;

	return 0;
}