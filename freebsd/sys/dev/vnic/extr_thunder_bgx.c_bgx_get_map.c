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
typedef  int u_int ;

/* Variables and functions */
 int MAX_BGX_PER_CN88XX ; 
 scalar_t__* bgx_vnic ; 

u_int
bgx_get_map(int node)
{
	int i;
	u_int map = 0;

	for (i = 0; i < MAX_BGX_PER_CN88XX; i++) {
		if (bgx_vnic[(node * MAX_BGX_PER_CN88XX) + i])
			map |= (1 << i);
	}

	return (map);
}