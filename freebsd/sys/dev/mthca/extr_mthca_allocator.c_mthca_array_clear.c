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
struct TYPE_2__ {scalar_t__ used; int /*<<< orphan*/ ** page; } ;

/* Variables and functions */
 int MTHCA_ARRAY_MASK ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,struct mthca_array*,int,int,scalar_t__) ; 

void mthca_array_clear(struct mthca_array *array, int index)
{
	int p = (index * sizeof (void *)) >> PAGE_SHIFT;

	if (--array->page_list[p].used == 0) {
		free_page((unsigned long) array->page_list[p].page);
		array->page_list[p].page = NULL;
	} else
		array->page_list[p].page[index & MTHCA_ARRAY_MASK] = NULL;

	if (array->page_list[p].used < 0)
		pr_debug("Array %p index %d page %d with ref count %d < 0\n",
			 array, index, p, array->page_list[p].used);
}