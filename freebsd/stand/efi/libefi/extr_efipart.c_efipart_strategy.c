#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* d_dev; } ;
struct disk_devdesc {int d_offset; TYPE_2__ dd; } ;
struct devdesc {int dummy; } ;
struct bcache_devdata {int /*<<< orphan*/  dv_cache; void* dv_devdata; int /*<<< orphan*/  dv_strategy; } ;
struct TYPE_11__ {TYPE_4__* pd_blkio; int /*<<< orphan*/  pd_bcache; } ;
typedef  TYPE_5__ pdinfo_t ;
typedef  int daddr_t ;
struct TYPE_10__ {TYPE_3__* Media; } ;
struct TYPE_9__ {int BlockSize; int /*<<< orphan*/  MediaPresent; scalar_t__ RemovableMedia; } ;
struct TYPE_7__ {scalar_t__ dv_type; } ;

/* Variables and functions */
 scalar_t__ DEVT_DISK ; 
 int EINVAL ; 
 int ENXIO ; 
 int bcache_strategy (struct bcache_devdata*,int,int,size_t,char*,size_t*) ; 
 TYPE_5__* efiblk_get_pdinfo (struct devdesc*) ; 
 int /*<<< orphan*/  efipart_realstrategy ; 

__attribute__((used)) static int
efipart_strategy(void *devdata, int rw, daddr_t blk, size_t size,
    char *buf, size_t *rsize)
{
	struct bcache_devdata bcd;
	struct disk_devdesc *dev;
	pdinfo_t *pd;

	dev = (struct disk_devdesc *)devdata;
	if (dev == NULL)
		return (EINVAL);

	pd = efiblk_get_pdinfo((struct devdesc *)dev);
	if (pd == NULL)
		return (EINVAL);

	if (pd->pd_blkio->Media->RemovableMedia &&
	    !pd->pd_blkio->Media->MediaPresent)
		return (ENXIO);

	bcd.dv_strategy = efipart_realstrategy;
	bcd.dv_devdata = devdata;
	bcd.dv_cache = pd->pd_bcache;

	if (dev->dd.d_dev->dv_type == DEVT_DISK) {
		daddr_t offset;

		offset = dev->d_offset * pd->pd_blkio->Media->BlockSize;
		offset /= 512;
		return (bcache_strategy(&bcd, rw, blk + offset,
		    size, buf, rsize));
	}
	return (bcache_strategy(&bcd, rw, blk, size, buf, rsize));
}