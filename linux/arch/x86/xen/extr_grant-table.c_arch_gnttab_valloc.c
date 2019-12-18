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
struct gnttab_vm_area {int /*<<< orphan*/ * ptes; int /*<<< orphan*/ * area; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/ * alloc_vm_area (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arch_gnttab_valloc(struct gnttab_vm_area *area, unsigned nr_frames)
{
	area->ptes = kmalloc_array(nr_frames, sizeof(*area->ptes), GFP_KERNEL);
	if (area->ptes == NULL)
		return -ENOMEM;

	area->area = alloc_vm_area(PAGE_SIZE * nr_frames, area->ptes);
	if (area->area == NULL) {
		kfree(area->ptes);
		return -ENOMEM;
	}

	return 0;
}