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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 unsigned long PGDIR_SIZE ; 
 int /*<<< orphan*/ * pgd_offset_k (unsigned long) ; 
 int /*<<< orphan*/  unmap_uncached_pmd (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 

__attribute__((used)) static void unmap_uncached_pages(unsigned long vaddr, unsigned long size)
{
	pgd_t * dir;
	unsigned long end = vaddr + size;

	dir = pgd_offset_k(vaddr);
	do {
		unmap_uncached_pmd(dir, vaddr, end - vaddr);
		vaddr = vaddr + PGDIR_SIZE;
		dir++;
	} while (vaddr && (vaddr < end));
}