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
struct rsxx_cardinfo {int size8; int bdev_attached; int /*<<< orphan*/  dev_lock; int /*<<< orphan*/  gendisk; scalar_t__ config_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_TO_DEV (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  device_add_disk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ enable_blkdev ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_capacity (int /*<<< orphan*/ ,int) ; 

int rsxx_attach_dev(struct rsxx_cardinfo *card)
{
	mutex_lock(&card->dev_lock);

	/* The block device requires the stripe size from the config. */
	if (enable_blkdev) {
		if (card->config_valid)
			set_capacity(card->gendisk, card->size8 >> 9);
		else
			set_capacity(card->gendisk, 0);
		device_add_disk(CARD_TO_DEV(card), card->gendisk, NULL);
		card->bdev_attached = 1;
	}

	mutex_unlock(&card->dev_lock);

	return 0;
}