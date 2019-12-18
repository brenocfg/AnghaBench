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
typedef  scalar_t__ u_int ;

/* Variables and functions */
 scalar_t__ vm_min_waiters ; 
 scalar_t__ vm_pageproc_waiters ; 
 scalar_t__ vm_severe_waiters ; 

u_int
vm_wait_count(void)
{

	return (vm_severe_waiters + vm_min_waiters + vm_pageproc_waiters);
}