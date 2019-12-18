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
 int last_fd ; 
 int /*<<< orphan*/  ulog_logout_pseudo (int) ; 

int
utempter_remove_added_record(void)
{

	if (last_fd < 0)
		return (0);
	ulog_logout_pseudo(last_fd);
	last_fd = -1;
	return (0);
}