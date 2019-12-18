#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file {int dummy; } ;
struct TYPE_4__ {TYPE_1__* mm; } ;
struct TYPE_3__ {unsigned long (* get_unmapped_area ) (struct file*,unsigned long,unsigned long,unsigned long,unsigned long) ;} ;

/* Variables and functions */
 unsigned long ENOSYS ; 
 unsigned long MAP_SHARED ; 
 TYPE_2__* current ; 
 unsigned long shmem_get_unmapped_area (int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 unsigned long stub1 (struct file*,unsigned long,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long get_unmapped_area_zero(struct file *file,
				unsigned long addr, unsigned long len,
				unsigned long pgoff, unsigned long flags)
{
#ifdef CONFIG_MMU
	if (flags & MAP_SHARED) {
		/*
		 * mmap_zero() will call shmem_zero_setup() to create a file,
		 * so use shmem's get_unmapped_area in case it can be huge;
		 * and pass NULL for file as in mmap.c's get_unmapped_area(),
		 * so as not to confuse shmem with our handle on "/dev/zero".
		 */
		return shmem_get_unmapped_area(NULL, addr, len, pgoff, flags);
	}

	/* Otherwise flags & MAP_PRIVATE: with no shmem object beneath it */
	return current->mm->get_unmapped_area(file, addr, len, pgoff, flags);
#else
	return -ENOSYS;
#endif
}