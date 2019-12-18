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
typedef  scalar_t__ vm_ooffset_t ;

/* Variables and functions */
 scalar_t__ __predict_false (int) ; 
 scalar_t__ swap_pager_avail ; 
 scalar_t__ tmpfs_pages_reserved ; 
 scalar_t__ vm_free_count () ; 

size_t
tmpfs_mem_avail(void)
{
	vm_ooffset_t avail;

	avail = swap_pager_avail + vm_free_count() - tmpfs_pages_reserved;
	if (__predict_false(avail < 0))
		avail = 0;
	return (avail);
}