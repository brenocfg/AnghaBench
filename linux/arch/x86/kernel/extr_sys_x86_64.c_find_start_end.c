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
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 unsigned long DEFAULT_MAP_WINDOW ; 
 unsigned long MAP_32BIT ; 
 int PF_RANDOMIZE ; 
 TYPE_1__* current ; 
 unsigned long get_mmap_base (int) ; 
 scalar_t__ in_32bit_syscall () ; 
 unsigned long randomize_page (unsigned long,int) ; 
 unsigned long task_size_32bit () ; 
 unsigned long task_size_64bit (int) ; 

__attribute__((used)) static void find_start_end(unsigned long addr, unsigned long flags,
		unsigned long *begin, unsigned long *end)
{
	if (!in_32bit_syscall() && (flags & MAP_32BIT)) {
		/* This is usually used needed to map code in small
		   model, so it needs to be in the first 31bit. Limit
		   it to that.  This means we need to move the
		   unmapped base down for this case. This can give
		   conflicts with the heap, but we assume that glibc
		   malloc knows how to fall back to mmap. Give it 1GB
		   of playground for now. -AK */
		*begin = 0x40000000;
		*end = 0x80000000;
		if (current->flags & PF_RANDOMIZE) {
			*begin = randomize_page(*begin, 0x02000000);
		}
		return;
	}

	*begin	= get_mmap_base(1);
	if (in_32bit_syscall())
		*end = task_size_32bit();
	else
		*end = task_size_64bit(addr > DEFAULT_MAP_WINDOW);
}