#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; } ;
struct pktcdvd_device {TYPE_2__* bdev; int /*<<< orphan*/  flags; TYPE_1__ settings; int /*<<< orphan*/  disk; } ;
typedef  int loff_t ;
typedef  scalar_t__ fmode_t ;
struct TYPE_7__ {int /*<<< orphan*/  bd_disk; int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CDROM_PKTCDVD_BUFFERS ; 
 int ENOMEM ; 
 int FMODE_EXCL ; 
 int FMODE_READ ; 
 int /*<<< orphan*/  MAX_SPEED ; 
 int /*<<< orphan*/  PACKET_WRITABLE ; 
 int /*<<< orphan*/  bd_set_size (TYPE_2__*,int) ; 
 struct request_queue* bdev_get_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  bdget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (struct request_queue*,int /*<<< orphan*/ ) ; 
 int blkdev_get (TYPE_2__*,int,struct pktcdvd_device*) ; 
 int /*<<< orphan*/  blkdev_put (TYPE_2__*,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pkt_err (struct pktcdvd_device*,char*) ; 
 int pkt_get_last_written (struct pktcdvd_device*,long*) ; 
 int /*<<< orphan*/  pkt_grow_pktlist (struct pktcdvd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkt_info (struct pktcdvd_device*,char*,long) ; 
 int pkt_open_write (struct pktcdvd_device*) ; 
 int pkt_set_segment_merging (struct pktcdvd_device*,struct request_queue*) ; 
 int /*<<< orphan*/  pkt_set_speed (struct pktcdvd_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_capacity (int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static int pkt_open_dev(struct pktcdvd_device *pd, fmode_t write)
{
	int ret;
	long lba;
	struct request_queue *q;

	/*
	 * We need to re-open the cdrom device without O_NONBLOCK to be able
	 * to read/write from/to it. It is already opened in O_NONBLOCK mode
	 * so bdget() can't fail.
	 */
	bdget(pd->bdev->bd_dev);
	ret = blkdev_get(pd->bdev, FMODE_READ | FMODE_EXCL, pd);
	if (ret)
		goto out;

	ret = pkt_get_last_written(pd, &lba);
	if (ret) {
		pkt_err(pd, "pkt_get_last_written failed\n");
		goto out_putdev;
	}

	set_capacity(pd->disk, lba << 2);
	set_capacity(pd->bdev->bd_disk, lba << 2);
	bd_set_size(pd->bdev, (loff_t)lba << 11);

	q = bdev_get_queue(pd->bdev);
	if (write) {
		ret = pkt_open_write(pd);
		if (ret)
			goto out_putdev;
		/*
		 * Some CDRW drives can not handle writes larger than one packet,
		 * even if the size is a multiple of the packet size.
		 */
		blk_queue_max_hw_sectors(q, pd->settings.size);
		set_bit(PACKET_WRITABLE, &pd->flags);
	} else {
		pkt_set_speed(pd, MAX_SPEED, MAX_SPEED);
		clear_bit(PACKET_WRITABLE, &pd->flags);
	}

	ret = pkt_set_segment_merging(pd, q);
	if (ret)
		goto out_putdev;

	if (write) {
		if (!pkt_grow_pktlist(pd, CONFIG_CDROM_PKTCDVD_BUFFERS)) {
			pkt_err(pd, "not enough memory for buffers\n");
			ret = -ENOMEM;
			goto out_putdev;
		}
		pkt_info(pd, "%lukB available on disc\n", lba << 1);
	}

	return 0;

out_putdev:
	blkdev_put(pd->bdev, FMODE_READ | FMODE_EXCL);
out:
	return ret;
}