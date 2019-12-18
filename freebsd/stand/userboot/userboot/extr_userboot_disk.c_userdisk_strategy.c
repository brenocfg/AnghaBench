#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t d_unit; } ;
struct disk_devdesc {scalar_t__ d_offset; TYPE_1__ dd; } ;
struct bcache_devdata {int /*<<< orphan*/  dv_cache; void* dv_devdata; int /*<<< orphan*/  dv_strategy; } ;
typedef  scalar_t__ daddr_t ;
struct TYPE_4__ {int /*<<< orphan*/  ud_bcache; } ;

/* Variables and functions */
 int bcache_strategy (struct bcache_devdata*,int,scalar_t__,size_t,char*,size_t*) ; 
 TYPE_2__* ud_info ; 
 int /*<<< orphan*/  userdisk_realstrategy ; 

__attribute__((used)) static int
userdisk_strategy(void *devdata, int rw, daddr_t dblk, size_t size,
    char *buf, size_t *rsize)
{
	struct bcache_devdata bcd;
	struct disk_devdesc *dev;

	dev = (struct disk_devdesc *)devdata;
	bcd.dv_strategy = userdisk_realstrategy;
	bcd.dv_devdata = devdata;
	bcd.dv_cache = ud_info[dev->dd.d_unit].ud_bcache;
	return (bcache_strategy(&bcd, rw, dblk + dev->d_offset,
	    size, buf, rsize));
}