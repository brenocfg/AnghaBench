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
typedef  unsigned long off_t ;

/* Variables and functions */
 long EINVAL ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 long ksys_mmap_pgoff (unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 scalar_t__ unlikely (unsigned long) ; 

__attribute__((used)) static long riscv_sys_mmap(unsigned long addr, unsigned long len,
			   unsigned long prot, unsigned long flags,
			   unsigned long fd, off_t offset,
			   unsigned long page_shift_offset)
{
	if (unlikely(offset & (~PAGE_MASK >> page_shift_offset)))
		return -EINVAL;
	return ksys_mmap_pgoff(addr, len, prot, flags, fd,
			       offset >> (PAGE_SHIFT - page_shift_offset));
}