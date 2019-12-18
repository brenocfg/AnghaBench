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
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 scalar_t__ cold ; 
 int /*<<< orphan*/  usb_needs_explore_all () ; 

__attribute__((used)) static void
usb_needs_explore_init(void *arg)
{
	/*
	 * The cold variable should be cleared prior to this function
	 * being called:
	 */
	if (cold == 0)
		usb_needs_explore_all();
	else
		DPRINTFN(-1, "Cold variable is still set!\n");
}