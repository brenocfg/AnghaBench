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
struct xive_irq_bitmap {int base; int count; int /*<<< orphan*/  list; void* bitmap; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct xive_irq_bitmap*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xive_irq_bitmaps ; 

__attribute__((used)) static int xive_irq_bitmap_add(int base, int count)
{
	struct xive_irq_bitmap *xibm;

	xibm = kzalloc(sizeof(*xibm), GFP_KERNEL);
	if (!xibm)
		return -ENOMEM;

	spin_lock_init(&xibm->lock);
	xibm->base = base;
	xibm->count = count;
	xibm->bitmap = kzalloc(xibm->count, GFP_KERNEL);
	if (!xibm->bitmap) {
		kfree(xibm);
		return -ENOMEM;
	}
	list_add(&xibm->list, &xive_irq_bitmaps);

	pr_info("Using IRQ range [%x-%x]", xibm->base,
		xibm->base + xibm->count - 1);
	return 0;
}