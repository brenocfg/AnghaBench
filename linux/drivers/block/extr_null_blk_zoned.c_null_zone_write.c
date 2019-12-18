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
struct nullb_device {struct blk_zone* zones; } ;
struct nullb_cmd {int /*<<< orphan*/  error; TYPE_1__* nq; } ;
struct blk_zone {int cond; unsigned int wp; unsigned int start; unsigned int len; } ;
typedef  unsigned int sector_t ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {struct nullb_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
#define  BLK_ZONE_COND_EMPTY 131 
#define  BLK_ZONE_COND_FULL 130 
#define  BLK_ZONE_COND_IMP_OPEN 129 
#define  BLK_ZONE_COND_NOT_WP 128 
 unsigned int null_zone_no (struct nullb_device*,unsigned int) ; 

__attribute__((used)) static blk_status_t null_zone_write(struct nullb_cmd *cmd, sector_t sector,
		     unsigned int nr_sectors)
{
	struct nullb_device *dev = cmd->nq->dev;
	unsigned int zno = null_zone_no(dev, sector);
	struct blk_zone *zone = &dev->zones[zno];

	switch (zone->cond) {
	case BLK_ZONE_COND_FULL:
		/* Cannot write to a full zone */
		cmd->error = BLK_STS_IOERR;
		return BLK_STS_IOERR;
	case BLK_ZONE_COND_EMPTY:
	case BLK_ZONE_COND_IMP_OPEN:
		/* Writes must be at the write pointer position */
		if (sector != zone->wp)
			return BLK_STS_IOERR;

		if (zone->cond == BLK_ZONE_COND_EMPTY)
			zone->cond = BLK_ZONE_COND_IMP_OPEN;

		zone->wp += nr_sectors;
		if (zone->wp == zone->start + zone->len)
			zone->cond = BLK_ZONE_COND_FULL;
		break;
	case BLK_ZONE_COND_NOT_WP:
		break;
	default:
		/* Invalid zone condition */
		return BLK_STS_IOERR;
	}
	return BLK_STS_OK;
}