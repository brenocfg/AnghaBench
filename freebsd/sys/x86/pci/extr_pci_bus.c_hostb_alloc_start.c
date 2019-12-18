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
typedef  int rman_res_t ;

/* Variables and functions */
 int SYS_RES_IOPORT ; 
 int SYS_RES_MEMORY ; 
 int host_mem_start ; 

rman_res_t
hostb_alloc_start(int type, rman_res_t start, rman_res_t end, rman_res_t count)
{

	if (start + count - 1 != end) {
		if (type == SYS_RES_MEMORY && start < host_mem_start)
			start = host_mem_start;
		if (type == SYS_RES_IOPORT && start < 0x1000)
			start = 0x1000;
	}
	return (start);
}