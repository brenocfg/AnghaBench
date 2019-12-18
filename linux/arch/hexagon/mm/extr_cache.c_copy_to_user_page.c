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
struct vm_area_struct {int vm_flags; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int VM_EXEC ; 
 int /*<<< orphan*/  flush_icache_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

void copy_to_user_page(struct vm_area_struct *vma, struct page *page,
		       unsigned long vaddr, void *dst, void *src, int len)
{
	memcpy(dst, src, len);
	if (vma->vm_flags & VM_EXEC) {
		flush_icache_range((unsigned long) dst,
		(unsigned long) dst + len);
	}
}