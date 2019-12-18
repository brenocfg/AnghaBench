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
struct TYPE_2__ {int* start_vector; int length; int img_CRC; int CRC; } ;

/* Variables and functions */
 int NUMBER_VECTORS ; 
 TYPE_1__ img_header ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void print_header(void)
{
	int i;

	printf("vectors in header\n");
	for (i = 0; i < NUMBER_VECTORS; i++) {
		printf("%d:0x%08x\n", i, img_header.start_vector[i]);
	}
	printf("length:%8x\nimg_CRC:0x%08x\nHeader CRC:0x%08x\n",
		img_header.length, img_header.img_CRC, img_header.CRC);
}