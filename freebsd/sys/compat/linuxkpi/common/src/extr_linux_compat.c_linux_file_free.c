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
struct linux_file {int /*<<< orphan*/ * _file; int /*<<< orphan*/ * f_shmem; } ;

/* Variables and functions */
 int /*<<< orphan*/  _fdrop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  kfree (struct linux_file*) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ *) ; 

void
linux_file_free(struct linux_file *filp)
{
	if (filp->_file == NULL) {
		if (filp->f_shmem != NULL)
			vm_object_deallocate(filp->f_shmem);
		kfree(filp);
	} else {
		/*
		 * The close method of the character device or file
		 * will free the linux_file structure:
		 */
		_fdrop(filp->_file, curthread);
	}
}