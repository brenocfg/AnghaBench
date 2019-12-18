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
 unsigned long SHMLBA ; 

__attribute__((used)) static inline unsigned long COLOR_ALIGN(unsigned long addr,
					 unsigned long pgoff)
{
	unsigned long base = (addr+SHMLBA-1)&~(SHMLBA-1);
	unsigned long off = (pgoff<<PAGE_SHIFT) & (SHMLBA-1);

	return base + off;
}