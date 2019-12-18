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
struct nullb_device {size_t nr_zones; struct blk_zone* zones; } ;
struct nullb_cmd {int /*<<< orphan*/  rq; TYPE_1__* nq; } ;
struct blk_zone {int /*<<< orphan*/  start; int /*<<< orphan*/  wp; void* cond; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {struct nullb_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_NOTSUPP ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 void* BLK_ZONE_COND_EMPTY ; 
 int /*<<< orphan*/  BLK_ZONE_TYPE_CONVENTIONAL ; 
#define  REQ_OP_ZONE_RESET 129 
#define  REQ_OP_ZONE_RESET_ALL 128 
 unsigned int null_zone_no (struct nullb_device*,int /*<<< orphan*/ ) ; 
 int req_op (int /*<<< orphan*/ ) ; 

__attribute__((used)) static blk_status_t null_zone_reset(struct nullb_cmd *cmd, sector_t sector)
{
	struct nullb_device *dev = cmd->nq->dev;
	unsigned int zno = null_zone_no(dev, sector);
	struct blk_zone *zone = &dev->zones[zno];
	size_t i;

	switch (req_op(cmd->rq)) {
	case REQ_OP_ZONE_RESET_ALL:
		for (i = 0; i < dev->nr_zones; i++) {
			if (zone[i].type == BLK_ZONE_TYPE_CONVENTIONAL)
				continue;
			zone[i].cond = BLK_ZONE_COND_EMPTY;
			zone[i].wp = zone[i].start;
		}
		break;
	case REQ_OP_ZONE_RESET:
		if (zone->type == BLK_ZONE_TYPE_CONVENTIONAL)
			return BLK_STS_IOERR;

		zone->cond = BLK_ZONE_COND_EMPTY;
		zone->wp = zone->start;
		break;
	default:
		return BLK_STS_NOTSUPP;
	}
	return BLK_STS_OK;
}