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
struct vhd_geom {int cylinders; int heads; int sectors; } ;
typedef  int lba_t ;

/* Variables and functions */
 int VHD_SECTOR_SIZE ; 
 int ncyls ; 
 int nheads ; 
 int nsecs ; 

__attribute__((used)) static void
vhd_geometry(uint64_t image_size, struct vhd_geom *geom)
{
	lba_t imgsz;
	long cth;

	imgsz = image_size / VHD_SECTOR_SIZE;

	/* Respect command line options if possible. */
	if (nheads > 1 && nheads < 256 &&
	    nsecs > 1 && nsecs < 256 &&
	    ncyls < 65536) {
		geom->cylinders = (ncyls != 0) ? ncyls :
		    imgsz / (nheads * nsecs);
		geom->heads = nheads;
		geom->sectors = nsecs;
		return;
	}

	if (imgsz > 65536 * 16 * 255)
		imgsz = 65536 * 16 * 255;
	if (imgsz >= 65535 * 16 * 63) {
		geom->cylinders = imgsz / (16 * 255);
		geom->heads = 16;
		geom->sectors = 255;
		return;
	}
	geom->sectors = 17;
	cth = imgsz / 17;
	geom->heads = (cth + 1023) / 1024;
	if (geom->heads < 4)
		geom->heads = 4;
	if (cth >= (geom->heads * 1024) || geom->heads > 16) {
		geom->heads = 16;
		geom->sectors = 31;
		cth = imgsz / 31;
	}
	if (cth >= (geom->heads * 1024)) {
		geom->heads = 16;
		geom->sectors = 63;
		cth = imgsz / 63;
	}
	geom->cylinders = cth / geom->heads;
}