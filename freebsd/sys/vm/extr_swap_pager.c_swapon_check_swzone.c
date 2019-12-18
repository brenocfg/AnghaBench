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
 int /*<<< orphan*/  printf (char*,...) ; 
 int swap_maxpages ; 
 int swap_total ; 

__attribute__((used)) static void
swapon_check_swzone(void)
{

	/* recommend using no more than half that amount */
	if (swap_total > swap_maxpages / 2) {
		printf("warning: total configured swap (%lu pages) "
		    "exceeds maximum recommended amount (%lu pages).\n",
		    swap_total, swap_maxpages / 2);
		printf("warning: increase kern.maxswzone "
		    "or reduce amount of swap.\n");
	}
}