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
struct pktcdvd_device {int refcnt; int /*<<< orphan*/  flags; } ;
struct block_device {int /*<<< orphan*/  bd_dev; } ;
typedef  int fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CD_FRAMESIZE ; 
 int EBUSY ; 
 int ENODEV ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PACKET_WRITABLE ; 
 int /*<<< orphan*/  ctl_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct pktcdvd_device* pkt_find_dev_from_minor (int /*<<< orphan*/ ) ; 
 int pkt_open_dev (struct pktcdvd_device*,int) ; 
 int /*<<< orphan*/  pktcdvd_mutex ; 
 int /*<<< orphan*/  set_blocksize (struct block_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pkt_open(struct block_device *bdev, fmode_t mode)
{
	struct pktcdvd_device *pd = NULL;
	int ret;

	mutex_lock(&pktcdvd_mutex);
	mutex_lock(&ctl_mutex);
	pd = pkt_find_dev_from_minor(MINOR(bdev->bd_dev));
	if (!pd) {
		ret = -ENODEV;
		goto out;
	}
	BUG_ON(pd->refcnt < 0);

	pd->refcnt++;
	if (pd->refcnt > 1) {
		if ((mode & FMODE_WRITE) &&
		    !test_bit(PACKET_WRITABLE, &pd->flags)) {
			ret = -EBUSY;
			goto out_dec;
		}
	} else {
		ret = pkt_open_dev(pd, mode & FMODE_WRITE);
		if (ret)
			goto out_dec;
		/*
		 * needed here as well, since ext2 (among others) may change
		 * the blocksize at mount time
		 */
		set_blocksize(bdev, CD_FRAMESIZE);
	}

	mutex_unlock(&ctl_mutex);
	mutex_unlock(&pktcdvd_mutex);
	return 0;

out_dec:
	pd->refcnt--;
out:
	mutex_unlock(&ctl_mutex);
	mutex_unlock(&pktcdvd_mutex);
	return ret;
}