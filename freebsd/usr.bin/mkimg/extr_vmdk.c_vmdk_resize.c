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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint64_t ;
typedef  int lba_t ;

/* Variables and functions */
 int VMDK_IMAGE_ROUND ; 
 scalar_t__ VMDK_MIN_GRAIN_SIZE ; 
 scalar_t__ VMDK_SECTOR_SIZE ; 
 scalar_t__ blksz ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ grainsz ; 
 int image_set_size (int) ; 
 int secsz ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int
vmdk_resize(lba_t imgsz)
{
	uint64_t imagesz;

	imagesz = imgsz * secsz;
	imagesz = (imagesz + VMDK_IMAGE_ROUND - 1) & ~(VMDK_IMAGE_ROUND - 1);
	grainsz = (blksz < VMDK_MIN_GRAIN_SIZE) ? VMDK_MIN_GRAIN_SIZE : blksz;

	if (verbose)
		fprintf(stderr, "VMDK: image size = %ju, grain size = %ju\n",
		    (uintmax_t)imagesz, (uintmax_t)grainsz);

	grainsz /= VMDK_SECTOR_SIZE;
	return (image_set_size(imagesz / secsz));
}