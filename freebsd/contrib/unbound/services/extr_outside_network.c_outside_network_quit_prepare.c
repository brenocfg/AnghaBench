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
struct outside_network {int want_to_quit; } ;

/* Variables and functions */

void 
outside_network_quit_prepare(struct outside_network* outnet)
{
	if(!outnet)
		return;
	/* prevent queued items from being sent */
	outnet->want_to_quit = 1; 
}