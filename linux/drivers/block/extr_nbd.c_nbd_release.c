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
struct nbd_device {TYPE_1__* config; } ;
struct gendisk {struct nbd_device* private_data; } ;
struct block_device {scalar_t__ bd_openers; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {int /*<<< orphan*/  runtime_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NBD_RT_DISCONNECT_ON_CLOSE ; 
 struct block_device* bdget_disk (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nbd_config_put (struct nbd_device*) ; 
 int /*<<< orphan*/  nbd_disconnect_and_put (struct nbd_device*) ; 
 int /*<<< orphan*/  nbd_put (struct nbd_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nbd_release(struct gendisk *disk, fmode_t mode)
{
	struct nbd_device *nbd = disk->private_data;
	struct block_device *bdev = bdget_disk(disk, 0);

	if (test_bit(NBD_RT_DISCONNECT_ON_CLOSE, &nbd->config->runtime_flags) &&
			bdev->bd_openers == 0)
		nbd_disconnect_and_put(nbd);

	nbd_config_put(nbd);
	nbd_put(nbd);
}