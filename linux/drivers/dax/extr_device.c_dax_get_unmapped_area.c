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
struct file {struct dev_dax* private_data; } ;
struct dev_dax {struct dax_region* region; } ;
struct dax_region {unsigned long align; } ;
struct TYPE_4__ {TYPE_1__* mm; } ;
struct TYPE_3__ {unsigned long (* get_unmapped_area ) (struct file*,unsigned long,unsigned long,unsigned long,unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_VALUE (unsigned long) ; 
 unsigned long PAGE_SHIFT ; 
 TYPE_2__* current ; 
 unsigned long round_up (unsigned long,unsigned long) ; 
 unsigned long stub1 (struct file*,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 unsigned long stub2 (struct file*,unsigned long,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long dax_get_unmapped_area(struct file *filp,
		unsigned long addr, unsigned long len, unsigned long pgoff,
		unsigned long flags)
{
	unsigned long off, off_end, off_align, len_align, addr_align, align;
	struct dev_dax *dev_dax = filp ? filp->private_data : NULL;
	struct dax_region *dax_region;

	if (!dev_dax || addr)
		goto out;

	dax_region = dev_dax->region;
	align = dax_region->align;
	off = pgoff << PAGE_SHIFT;
	off_end = off + len;
	off_align = round_up(off, align);

	if ((off_end <= off_align) || ((off_end - off_align) < align))
		goto out;

	len_align = len + align;
	if ((off + len_align) < off)
		goto out;

	addr_align = current->mm->get_unmapped_area(filp, addr, len_align,
			pgoff, flags);
	if (!IS_ERR_VALUE(addr_align)) {
		addr_align += (off - addr_align) & (align - 1);
		return addr_align;
	}
 out:
	return current->mm->get_unmapped_area(filp, addr, len, pgoff, flags);
}