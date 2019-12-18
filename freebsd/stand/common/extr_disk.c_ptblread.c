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
typedef  int uint64_t ;
struct open_disk {int sectorsize; } ;
struct TYPE_4__ {TYPE_1__* d_dev; scalar_t__ d_opendata; } ;
struct disk_devdesc {TYPE_2__ dd; } ;
struct TYPE_3__ {int (* dv_strategy ) (struct disk_devdesc*,int,int,size_t,char*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int F_NORA ; 
 int F_READ ; 
 int stub1 (struct disk_devdesc*,int,int,size_t,char*,int /*<<< orphan*/ *) ; 

int
ptblread(void *d, void *buf, size_t blocks, uint64_t offset)
{
	struct disk_devdesc *dev;
	struct open_disk *od;

	dev = (struct disk_devdesc *)d;
	od = (struct open_disk *)dev->dd.d_opendata;

	/*
	 * The strategy function assumes the offset is in units of 512 byte
	 * sectors. For larger sector sizes, we need to adjust the offset to
	 * match the actual sector size.
	 */
	offset *= (od->sectorsize / 512);
	/*
	 * As the GPT backup partition is located at the end of the disk,
	 * to avoid reading past disk end, flag bcache not to use RA.
	 */
	return (dev->dd.d_dev->dv_strategy(dev, F_READ | F_NORA, offset,
	    blocks * od->sectorsize, (char *)buf, NULL));
}