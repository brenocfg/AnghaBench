#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ act_entry; int act_page; scalar_t__ act_area; TYPE_2__* debug_info_snap; } ;
typedef  TYPE_1__ file_private_info_t ;
struct TYPE_5__ {scalar_t__ entry_size; int pages_per_area; scalar_t__ nr_areas; int /*<<< orphan*/  areas; } ;
typedef  TYPE_2__ debug_info_t ;

/* Variables and functions */
 scalar_t__ DEBUG_PROLOG_ENTRY ; 
 scalar_t__ PAGE_SIZE ; 

__attribute__((used)) static inline int debug_next_entry(file_private_info_t *p_info)
{
	debug_info_t *id;

	id = p_info->debug_info_snap;
	if (p_info->act_entry == DEBUG_PROLOG_ENTRY) {
		p_info->act_entry = 0;
		p_info->act_page  = 0;
		goto out;
	}
	if (!id->areas)
		return 1;
	p_info->act_entry += id->entry_size;
	/* switch to next page, if we reached the end of the page  */
	if (p_info->act_entry > (PAGE_SIZE - id->entry_size)) {
		/* next page */
		p_info->act_entry = 0;
		p_info->act_page += 1;
		if ((p_info->act_page % id->pages_per_area) == 0) {
			/* next area */
			p_info->act_area++;
			p_info->act_page = 0;
		}
		if (p_info->act_area >= id->nr_areas)
			return 1;
	}
out:
	return 0;
}