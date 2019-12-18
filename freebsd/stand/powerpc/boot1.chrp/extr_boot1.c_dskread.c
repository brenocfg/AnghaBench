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
typedef  int uint64_t ;

/* Variables and functions */
 int DEV_BSIZE ; 
 int /*<<< orphan*/  bootdev ; 
 int /*<<< orphan*/  ofw_read (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  ofw_seek (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
dskread(void *buf, uint64_t lba, int nblk)
{
	/*
	 * The Open Firmware should open the correct partition for us.
	 * That means, if we read from offset zero on an open instance handle,
	 * we should read from offset zero of that partition.
	 */
	ofw_seek(bootdev, lba * DEV_BSIZE);
	ofw_read(bootdev, buf, nblk * DEV_BSIZE);
	return (0);
}