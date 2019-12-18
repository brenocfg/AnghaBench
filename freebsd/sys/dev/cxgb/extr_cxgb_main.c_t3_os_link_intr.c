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
struct port_info {int /*<<< orphan*/  link_check_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct port_info*) ; 
 int hz ; 
 int /*<<< orphan*/  link_check_callout ; 

void
t3_os_link_intr(struct port_info *pi)
{
	/*
	 * Schedule a link check in the near future.  If the link is flapping
	 * rapidly we'll keep resetting the callout and delaying the check until
	 * things stabilize a bit.
	 */
	callout_reset(&pi->link_check_ch, hz / 4, link_check_callout, pi);
}