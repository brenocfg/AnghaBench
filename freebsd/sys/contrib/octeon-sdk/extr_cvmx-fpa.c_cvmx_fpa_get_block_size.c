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

/* Variables and functions */
 int CVMX_FPA_POOL_0_SIZE ; 
 int CVMX_FPA_POOL_1_SIZE ; 
 int CVMX_FPA_POOL_2_SIZE ; 
 int CVMX_FPA_POOL_3_SIZE ; 
 int CVMX_FPA_POOL_4_SIZE ; 
 int CVMX_FPA_POOL_5_SIZE ; 
 int CVMX_FPA_POOL_6_SIZE ; 
 int CVMX_FPA_POOL_7_SIZE ; 

uint64_t cvmx_fpa_get_block_size(uint64_t pool)
{
    switch (pool)
    {
        case 0:
	    return CVMX_FPA_POOL_0_SIZE;
        case 1:
	    return CVMX_FPA_POOL_1_SIZE;
        case 2:
	    return CVMX_FPA_POOL_2_SIZE;
        case 3:
	    return CVMX_FPA_POOL_3_SIZE;
        case 4:
	    return CVMX_FPA_POOL_4_SIZE;
        case 5:
	    return CVMX_FPA_POOL_5_SIZE;
        case 6:
	    return CVMX_FPA_POOL_6_SIZE;
        case 7:
	    return CVMX_FPA_POOL_7_SIZE;
        default:
	    return 0;
    }
}