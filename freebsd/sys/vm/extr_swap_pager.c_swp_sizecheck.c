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
 scalar_t__ nswap_hiwat ; 
 scalar_t__ nswap_lowat ; 
 int /*<<< orphan*/  printf (char*) ; 
 int swap_pager_almost_full ; 
 scalar_t__ swap_pager_avail ; 
 scalar_t__ swap_pager_full ; 

__attribute__((used)) static void
swp_sizecheck(void)
{

	if (swap_pager_avail < nswap_lowat) {
		if (swap_pager_almost_full == 0) {
			printf("swap_pager: out of swap space\n");
			swap_pager_almost_full = 1;
		}
	} else {
		swap_pager_full = 0;
		if (swap_pager_avail > nswap_hiwat)
			swap_pager_almost_full = 0;
	}
}