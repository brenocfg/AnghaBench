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
 int /*<<< orphan*/  linux_osd_jail_slot ; 
 int /*<<< orphan*/  osd_jail_deregister (int /*<<< orphan*/ ) ; 

void
linux_osd_jail_deregister(void)
{

	osd_jail_deregister(linux_osd_jail_slot);
}