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
typedef  scalar_t__ uint64_t ;
typedef  int u_int ;
struct open_disk {int sectorsize; } ;
struct TYPE_4__ {TYPE_1__* d_dev; scalar_t__ d_opendata; } ;
struct disk_devdesc {scalar_t__ d_offset; TYPE_2__ dd; } ;
struct TYPE_3__ {int (* dv_strategy ) (struct disk_devdesc*,int /*<<< orphan*/ ,scalar_t__,int,void*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  F_WRITE ; 
 int stub1 (struct disk_devdesc*,int /*<<< orphan*/ ,scalar_t__,int,void*,int /*<<< orphan*/ *) ; 

int
disk_write(struct disk_devdesc *dev, void *buf, uint64_t offset, u_int blocks)
{
	struct open_disk *od;
	int ret;

	od = (struct open_disk *)dev->dd.d_opendata;
	ret = dev->dd.d_dev->dv_strategy(dev, F_WRITE, dev->d_offset + offset,
	    blocks * od->sectorsize, buf, NULL);

	return (ret);
}