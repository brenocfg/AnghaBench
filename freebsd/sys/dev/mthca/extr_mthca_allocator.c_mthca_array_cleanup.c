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
struct TYPE_2__ {scalar_t__ page; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

void mthca_array_cleanup(struct mthca_array *array, int nent)
{
	int i;

	for (i = 0; i < (nent * sizeof (void *) + PAGE_SIZE - 1) / PAGE_SIZE; ++i)
		free_page((unsigned long) array->page_list[i].page);

	kfree(array->page_list);
}