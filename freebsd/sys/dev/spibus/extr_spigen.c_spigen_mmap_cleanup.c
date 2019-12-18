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
struct spigen_mmap {scalar_t__ kvaddr; int bufsize; int /*<<< orphan*/ * bufobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  free (struct spigen_mmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_qremove (scalar_t__,int) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
spigen_mmap_cleanup(void *arg)
{
	struct spigen_mmap *mmap = arg;

	if (mmap->kvaddr != 0)
		pmap_qremove(mmap->kvaddr, mmap->bufsize / PAGE_SIZE);
	if (mmap->bufobj != NULL)
		vm_object_deallocate(mmap->bufobj);
	free(mmap, M_DEVBUF);
}