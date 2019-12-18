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
struct work_struct {int dummy; } ;
struct bio {struct bio* bi_private; } ;

/* Variables and functions */
 struct bio* bio_dirty_list ; 
 int /*<<< orphan*/  bio_dirty_lock ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_release_pages (struct bio*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bio_dirty_fn(struct work_struct *work)
{
	struct bio *bio, *next;

	spin_lock_irq(&bio_dirty_lock);
	next = bio_dirty_list;
	bio_dirty_list = NULL;
	spin_unlock_irq(&bio_dirty_lock);

	while ((bio = next) != NULL) {
		next = bio->bi_private;

		bio_release_pages(bio, true);
		bio_put(bio);
	}
}