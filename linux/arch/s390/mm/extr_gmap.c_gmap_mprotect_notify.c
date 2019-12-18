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
 int EINVAL ; 
 int /*<<< orphan*/  GMAP_NOTIFY_MPROT ; 
 int /*<<< orphan*/  MACHINE_HAS_ESOP ; 
 unsigned long PAGE_MASK ; 
 int PROT_READ ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ gmap_is_shadow (struct gmap*) ; 
 int gmap_protect_range (struct gmap*,unsigned long,unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int gmap_mprotect_notify(struct gmap *gmap, unsigned long gaddr,
			 unsigned long len, int prot)
{
	int rc;

	if ((gaddr & ~PAGE_MASK) || (len & ~PAGE_MASK) || gmap_is_shadow(gmap))
		return -EINVAL;
	if (!MACHINE_HAS_ESOP && prot == PROT_READ)
		return -EINVAL;
	down_read(&gmap->mm->mmap_sem);
	rc = gmap_protect_range(gmap, gaddr, len, prot, GMAP_NOTIFY_MPROT);
	up_read(&gmap->mm->mmap_sem);
	return rc;
}