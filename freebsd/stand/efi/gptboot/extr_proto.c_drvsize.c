#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct dsk {scalar_t__ devinfo; } ;
struct TYPE_5__ {TYPE_3__* dev; } ;
typedef  TYPE_2__ dev_info_t ;
struct TYPE_6__ {TYPE_1__* Media; } ;
struct TYPE_4__ {scalar_t__ LastBlock; } ;
typedef  TYPE_3__ EFI_BLOCK_IO ;

/* Variables and functions */

uint64_t
drvsize(struct dsk *dskp)
{
	dev_info_t *devinfo = (dev_info_t *)dskp->devinfo;
	EFI_BLOCK_IO *dev = devinfo->dev;

	return (dev->Media->LastBlock + 1);
}