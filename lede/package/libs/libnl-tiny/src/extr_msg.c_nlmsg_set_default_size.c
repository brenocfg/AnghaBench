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
 size_t default_msg_size ; 
 size_t nlmsg_total_size (int /*<<< orphan*/ ) ; 

void nlmsg_set_default_size(size_t max)
{
	if (max < nlmsg_total_size(0))
		max = nlmsg_total_size(0);

	default_msg_size = max;
}