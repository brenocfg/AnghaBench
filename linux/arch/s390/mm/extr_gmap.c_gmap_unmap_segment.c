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
struct gmap {TYPE_1__* mm; } ;
struct TYPE_2__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int PMD_SIZE ; 
 int __gmap_unmap_by_gaddr (struct gmap*,unsigned long) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gmap_flush_tlb (struct gmap*) ; 
 int /*<<< orphan*/  gmap_is_shadow (struct gmap*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int gmap_unmap_segment(struct gmap *gmap, unsigned long to, unsigned long len)
{
	unsigned long off;
	int flush;

	BUG_ON(gmap_is_shadow(gmap));
	if ((to | len) & (PMD_SIZE - 1))
		return -EINVAL;
	if (len == 0 || to + len < to)
		return -EINVAL;

	flush = 0;
	down_write(&gmap->mm->mmap_sem);
	for (off = 0; off < len; off += PMD_SIZE)
		flush |= __gmap_unmap_by_gaddr(gmap, to + off);
	up_write(&gmap->mm->mmap_sem);
	if (flush)
		gmap_flush_tlb(gmap);
	return 0;
}