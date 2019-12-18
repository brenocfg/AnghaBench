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
struct mthca_array {TYPE_1__* page_list; } ;
struct TYPE_2__ {void** page; int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MTHCA_ARRAY_MASK ; 
 int PAGE_SHIFT ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 

int mthca_array_set(struct mthca_array *array, int index, void *value)
{
	int p = (index * sizeof (void *)) >> PAGE_SHIFT;

	/* Allocate with GFP_ATOMIC because we'll be called with locks held. */
	if (!array->page_list[p].page)
		array->page_list[p].page = (void **) get_zeroed_page(GFP_ATOMIC);

	if (!array->page_list[p].page)
		return -ENOMEM;

	array->page_list[p].page[index & MTHCA_ARRAY_MASK] = value;
	++array->page_list[p].used;

	return 0;
}