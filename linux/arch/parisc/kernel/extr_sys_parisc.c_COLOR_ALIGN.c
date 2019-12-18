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

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 unsigned long SHM_COLOUR ; 
 unsigned long shared_align_offset (unsigned int,unsigned long) ; 

__attribute__((used)) static inline unsigned long COLOR_ALIGN(unsigned long addr,
			 unsigned int last_mmap, unsigned long pgoff)
{
	unsigned long base = (addr+SHM_COLOUR-1) & ~(SHM_COLOUR-1);
	unsigned long off  = (SHM_COLOUR-1) &
		(shared_align_offset(last_mmap, pgoff) << PAGE_SHIFT);

	return base + off;
}