#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_3__ {size_t* vaddr; int length; } ;
typedef  TYPE_1__ ocs_scsi_vaddr_len_t ;

/* Variables and functions */

uint16_t
ocs_scsi_dif_calc_checksum(ocs_scsi_vaddr_len_t addrlen[], uint32_t addrlen_count)
{
	uint32_t i, j;
	uint16_t checksum;
	uint32_t intermediate; /* Use an intermediate to hold more than 16 bits during calculations */
	uint32_t count;
	uint16_t *buffer;

	intermediate = 0;
	for (j = 0; j < addrlen_count; j++) {
		buffer = addrlen[j].vaddr;
		count = addrlen[j].length / 2;
		for (i=0; i < count; i++) {
			intermediate += buffer[i];
		}
	}

	/* Carry is everything over 16 bits */
	intermediate += ((intermediate & 0xffff0000) >> 16);

	/* Flip all the bits */
	intermediate = ~intermediate;

	checksum = intermediate;

	return checksum;
}