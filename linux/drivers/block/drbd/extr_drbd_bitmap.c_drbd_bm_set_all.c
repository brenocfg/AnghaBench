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
struct drbd_device {struct drbd_bitmap* bitmap; } ;
struct drbd_bitmap {int /*<<< orphan*/  bm_lock; int /*<<< orphan*/  bm_bits; int /*<<< orphan*/  bm_set; int /*<<< orphan*/  bm_words; struct drbd_bitmap* bm_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  bm_clear_surplus (struct drbd_bitmap*) ; 
 int /*<<< orphan*/  bm_memset (struct drbd_bitmap*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (struct drbd_bitmap*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void drbd_bm_set_all(struct drbd_device *device)
{
	struct drbd_bitmap *b = device->bitmap;
	if (!expect(b))
		return;
	if (!expect(b->bm_pages))
		return;

	spin_lock_irq(&b->bm_lock);
	bm_memset(b, 0, 0xff, b->bm_words);
	(void)bm_clear_surplus(b);
	b->bm_set = b->bm_bits;
	spin_unlock_irq(&b->bm_lock);
}