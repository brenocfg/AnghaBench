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
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; int /*<<< orphan*/  vm_page_prot; } ;
struct file {struct bsr_dev* private_data; } ;
struct bsr_dev {unsigned long bsr_len; int bsr_addr; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int io_remap_pfn_range (struct vm_area_struct*,unsigned long,int,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int remap_4k_pfn (struct vm_area_struct*,unsigned long,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bsr_mmap(struct file *filp, struct vm_area_struct *vma)
{
	unsigned long size   = vma->vm_end - vma->vm_start;
	struct bsr_dev *dev = filp->private_data;
	int ret;

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	/* check for the case of a small BSR device and map one 4k page for it*/
	if (dev->bsr_len < PAGE_SIZE && size == PAGE_SIZE)
		ret = remap_4k_pfn(vma, vma->vm_start, dev->bsr_addr >> 12,
				   vma->vm_page_prot);
	else if (size <= dev->bsr_len)
		ret = io_remap_pfn_range(vma, vma->vm_start,
					 dev->bsr_addr >> PAGE_SHIFT,
					 size, vma->vm_page_prot);
	else
		return -EINVAL;

	if (ret)
		return -EAGAIN;

	return 0;
}