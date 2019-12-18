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
struct vma_data {int vm_end; int vm_start; unsigned long* maddr; int /*<<< orphan*/  refcnt; } ;
struct vm_area_struct {struct vma_data* vm_private_data; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  kvfree (struct vma_data*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uncached_free_page (unsigned long,int) ; 

__attribute__((used)) static void
mspec_close(struct vm_area_struct *vma)
{
	struct vma_data *vdata;
	int index, last_index;
	unsigned long my_page;

	vdata = vma->vm_private_data;

	if (!refcount_dec_and_test(&vdata->refcnt))
		return;

	last_index = (vdata->vm_end - vdata->vm_start) >> PAGE_SHIFT;
	for (index = 0; index < last_index; index++) {
		if (vdata->maddr[index] == 0)
			continue;
		/*
		 * Clear the page before sticking it back
		 * into the pool.
		 */
		my_page = vdata->maddr[index];
		vdata->maddr[index] = 0;
		memset((char *)my_page, 0, PAGE_SIZE);
		uncached_free_page(my_page, 1);
	}

	kvfree(vdata);
}