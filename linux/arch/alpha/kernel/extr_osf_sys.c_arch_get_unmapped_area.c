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
struct file {int dummy; } ;
struct TYPE_2__ {int personality; } ;

/* Variables and functions */
 int ADDR_LIMIT_32BIT ; 
 unsigned long ENOMEM ; 
 unsigned long MAP_FIXED ; 
 int /*<<< orphan*/  PAGE_ALIGN (unsigned long) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 unsigned long TASK_SIZE ; 
 unsigned long TASK_UNMAPPED_BASE ; 
 unsigned long arch_get_unmapped_area_1 (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 TYPE_1__* current ; 

unsigned long
arch_get_unmapped_area(struct file *filp, unsigned long addr,
		       unsigned long len, unsigned long pgoff,
		       unsigned long flags)
{
	unsigned long limit;

	/* "32 bit" actually means 31 bit, since pointers sign extend.  */
	if (current->personality & ADDR_LIMIT_32BIT)
		limit = 0x80000000;
	else
		limit = TASK_SIZE;

	if (len > limit)
		return -ENOMEM;

	if (flags & MAP_FIXED)
		return addr;

	/* First, see if the given suggestion fits.

	   The OSF/1 loader (/sbin/loader) relies on us returning an
	   address larger than the requested if one exists, which is
	   a terribly broken way to program.

	   That said, I can see the use in being able to suggest not
	   merely specific addresses, but regions of memory -- perhaps
	   this feature should be incorporated into all ports?  */

	if (addr) {
		addr = arch_get_unmapped_area_1 (PAGE_ALIGN(addr), len, limit);
		if (addr != (unsigned long) -ENOMEM)
			return addr;
	}

	/* Next, try allocating at TASK_UNMAPPED_BASE.  */
	addr = arch_get_unmapped_area_1 (PAGE_ALIGN(TASK_UNMAPPED_BASE),
					 len, limit);
	if (addr != (unsigned long) -ENOMEM)
		return addr;

	/* Finally, try allocating in low memory.  */
	addr = arch_get_unmapped_area_1 (PAGE_SIZE, len, limit);

	return addr;
}