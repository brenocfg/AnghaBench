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
typedef  int uint32_t ;

/* Variables and functions */
 int H5_TEMP_BASE ; 
 int H5_TEMP_BASE_CPU ; 
 int H5_TEMP_BASE_GPU ; 
 int H5_TEMP_DIV ; 
 int H5_TEMP_MUL ; 
 int H5_TEMP_MUL_CPU ; 
 int H5_TEMP_MUL_GPU ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
h5_to_temp(uint32_t val, int sensor)
{
	int tmp;

	/* Temp is lower than 70 degrees */
	if (val > 0x500) {
		tmp = H5_TEMP_BASE - (val * H5_TEMP_MUL);
		tmp >>= H5_TEMP_DIV;
		return (tmp);
	}

	if (sensor == 0)
		tmp = H5_TEMP_BASE_CPU - (val * H5_TEMP_MUL_CPU);
	else if (sensor == 1)
		tmp = H5_TEMP_BASE_GPU - (val * H5_TEMP_MUL_GPU);
	else {
		printf("Unknown sensor %d\n", sensor);
		return (val);
	}

	tmp >>= H5_TEMP_DIV;
	return (tmp);
}