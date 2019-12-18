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
struct agp_memory {int type; int num_scratch_pages; scalar_t__ page_count; int /*<<< orphan*/ ** pages; } ;

/* Variables and functions */
 size_t ENTRIES_PER_PAGE ; 
 struct agp_memory* agp_create_user_memory (size_t) ; 

struct agp_memory *agp_generic_alloc_user(size_t page_count, int type)
{
	struct agp_memory *new;
	int i;
	int pages;

	pages = (page_count + ENTRIES_PER_PAGE - 1) / ENTRIES_PER_PAGE;
	new = agp_create_user_memory(page_count);
	if (new == NULL)
		return NULL;

	for (i = 0; i < page_count; i++)
		new->pages[i] = NULL;
	new->page_count = 0;
	new->type = type;
	new->num_scratch_pages = pages;

	return new;
}