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

/* Variables and functions */
 int CVMX_CACHE_LINE_SIZE ; 
 int cvmx_l2c_get_num_assoc () ; 
 int cvmx_l2c_get_num_sets () ; 

int cvmx_l2c_get_cache_size_bytes(void)
{
	return cvmx_l2c_get_num_sets() * cvmx_l2c_get_num_assoc() *
		CVMX_CACHE_LINE_SIZE;
}