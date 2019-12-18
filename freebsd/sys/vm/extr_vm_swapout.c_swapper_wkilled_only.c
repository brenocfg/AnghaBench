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
 scalar_t__ SWAPIN_INTERVAL ; 
 int /*<<< orphan*/  all_domains ; 
 scalar_t__ last_swapin ; 
 scalar_t__ swap_inprogress ; 
 scalar_t__ ticks ; 
 scalar_t__ vm_page_count_min_set (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
swapper_wkilled_only(void)
{

	return (vm_page_count_min_set(&all_domains) || swap_inprogress > 0 ||
	    (u_int)(ticks - last_swapin) < SWAPIN_INTERVAL);
}