#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* active_entries; size_t active_area; scalar_t__ entry_size; int* active_pages; int pages_per_area; } ;
typedef  TYPE_1__ debug_info_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 

__attribute__((used)) static inline void proceed_active_entry(debug_info_t *id)
{
	if ((id->active_entries[id->active_area] += id->entry_size)
	    > (PAGE_SIZE - id->entry_size)) {
		id->active_entries[id->active_area] = 0;
		id->active_pages[id->active_area] =
			(id->active_pages[id->active_area] + 1) %
			id->pages_per_area;
	}
}