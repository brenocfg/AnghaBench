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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
#define  PPB_BYTE 129 
#define  PPB_NIBBLE 128 
 int spp_1284_read (int /*<<< orphan*/ ,int,char*,int,int*) ; 

int
ppb_1284_read(device_t bus, int mode, char *buffer,
		int max, int *read)
{
	int error = 0;

	switch (mode) {
	case PPB_NIBBLE:
	case PPB_BYTE:
		error = spp_1284_read(bus, mode, buffer, max, read);
		break;
	default:
		return (EINVAL);
	}

	return (error);
}