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
struct TYPE_2__ {int /*<<< orphan*/  thread; int /*<<< orphan*/  pending_bios; } ;
struct pktcdvd_device {scalar_t__ pkt_dev; int /*<<< orphan*/  name; TYPE_1__ cdrw; struct block_device* bdev; } ;
struct block_device {scalar_t__ bd_dev; } ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  CD_FRAMESIZE ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int FMODE_NDELAY ; 
 int FMODE_READ ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MAX_WRITERS ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdev_get_queue (struct block_device*) ; 
 int /*<<< orphan*/  bdevname (struct block_device*,char*) ; 
 struct block_device* bdget (scalar_t__) ; 
 int /*<<< orphan*/  blk_queue_scsi_passthrough (int /*<<< orphan*/ ) ; 
 int blkdev_get (struct block_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blkdev_put (struct block_device*,int) ; 
 int /*<<< orphan*/  kcdrwd ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct pktcdvd_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkt_dbg (int,struct pktcdvd_device*,char*,int /*<<< orphan*/ ) ; 
 struct pktcdvd_device** pkt_devs ; 
 int /*<<< orphan*/  pkt_err (struct pktcdvd_device*,char*,...) ; 
 int /*<<< orphan*/  pkt_init_queue (struct pktcdvd_device*) ; 
 int /*<<< orphan*/  pkt_proc ; 
 int /*<<< orphan*/  pkt_seq_show ; 
 int /*<<< orphan*/  proc_create_single_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pktcdvd_device*) ; 
 int /*<<< orphan*/  set_blocksize (struct block_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pkt_new_dev(struct pktcdvd_device *pd, dev_t dev)
{
	int i;
	int ret = 0;
	char b[BDEVNAME_SIZE];
	struct block_device *bdev;

	if (pd->pkt_dev == dev) {
		pkt_err(pd, "recursive setup not allowed\n");
		return -EBUSY;
	}
	for (i = 0; i < MAX_WRITERS; i++) {
		struct pktcdvd_device *pd2 = pkt_devs[i];
		if (!pd2)
			continue;
		if (pd2->bdev->bd_dev == dev) {
			pkt_err(pd, "%s already setup\n",
				bdevname(pd2->bdev, b));
			return -EBUSY;
		}
		if (pd2->pkt_dev == dev) {
			pkt_err(pd, "can't chain pktcdvd devices\n");
			return -EBUSY;
		}
	}

	bdev = bdget(dev);
	if (!bdev)
		return -ENOMEM;
	ret = blkdev_get(bdev, FMODE_READ | FMODE_NDELAY, NULL);
	if (ret)
		return ret;
	if (!blk_queue_scsi_passthrough(bdev_get_queue(bdev))) {
		blkdev_put(bdev, FMODE_READ | FMODE_NDELAY);
		return -EINVAL;
	}

	/* This is safe, since we have a reference from open(). */
	__module_get(THIS_MODULE);

	pd->bdev = bdev;
	set_blocksize(bdev, CD_FRAMESIZE);

	pkt_init_queue(pd);

	atomic_set(&pd->cdrw.pending_bios, 0);
	pd->cdrw.thread = kthread_run(kcdrwd, pd, "%s", pd->name);
	if (IS_ERR(pd->cdrw.thread)) {
		pkt_err(pd, "can't start kernel thread\n");
		ret = -ENOMEM;
		goto out_mem;
	}

	proc_create_single_data(pd->name, 0, pkt_proc, pkt_seq_show, pd);
	pkt_dbg(1, pd, "writer mapped to %s\n", bdevname(bdev, b));
	return 0;

out_mem:
	blkdev_put(bdev, FMODE_READ | FMODE_NDELAY);
	/* This is safe: open() is still holding a reference. */
	module_put(THIS_MODULE);
	return ret;
}