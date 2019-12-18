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
typedef  int lba_t ;

/* Variables and functions */
 int image_set_size (int) ; 
 int secsz ; 
 int vhd_resize (int) ; 

__attribute__((used)) static int
vhd_dyn_resize(lba_t imgsz)
{
	uint64_t imagesz;

	imagesz = vhd_resize(imgsz * secsz);
	return (image_set_size(imagesz / secsz));
}