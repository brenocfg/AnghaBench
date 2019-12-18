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
struct disk {int d_mediasize; int d_sectorsize; int d_fwsectors; int d_fwheads; } ;
typedef  int off_t ;

/* Variables and functions */

void
sparc64_ata_disk_firmware_geom_adjust(struct disk *disk)
{

	/*
	 * The VTOC8 disk label only uses 16-bit fields for cylinders, heads
	 * and sectors so the geometry of large disks has to be adjusted.
	 * If the disk is > 32GB at 16 heads and 63 sectors, adjust to 255
	 * sectors (this matches what the OpenSolaris dad(7D) driver does).
	 * If the disk is even > 128GB, additionally adjust the heads to
	 * 255.  This allows disks up to the 2TB limit of the extended VTOC8.
	 * XXX the OpenSolaris dad(7D) driver limits the mediasize to 128GB.
	 */
	if (disk->d_mediasize > (off_t)65535 * 16 * 63 * disk->d_sectorsize)
		disk->d_fwsectors = 255;
	if (disk->d_mediasize > (off_t)65535 * 16 * 255 * disk->d_sectorsize)
		disk->d_fwheads = 255;
}