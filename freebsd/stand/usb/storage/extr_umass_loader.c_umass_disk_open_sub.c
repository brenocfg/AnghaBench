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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct disk_devdesc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EINVAL ; 
 int disk_open (struct disk_devdesc*,int,scalar_t__) ; 
 TYPE_1__ umass_uaa ; 
 scalar_t__ usb_msc_read_capacity (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int
umass_disk_open_sub(struct disk_devdesc *dev)
{
	uint32_t nblock;
	uint32_t blocksize;

	if (usb_msc_read_capacity(umass_uaa.device, 0, &nblock, &blocksize) != 0)
		return (EINVAL);

	return (disk_open(dev, ((uint64_t)nblock + 1) * (uint64_t)blocksize, blocksize));
}