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
typedef  int u_int8_t ;
struct smapi_bios_header {int length; } ;

/* Variables and functions */

__attribute__((used)) static int
smapi_header_cksum (struct smapi_bios_header *header)
{
	u_int8_t *ptr;
	u_int8_t cksum;
	int i;

	ptr = (u_int8_t *)header;
	cksum = 0;
	for (i = 0; i < header->length; i++) {
		cksum += ptr[i];	
	}

	return (cksum);
}