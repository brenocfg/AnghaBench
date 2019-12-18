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
struct vop_poll_args {int a_events; } ;

/* Variables and functions */
 int POLLHUP ; 
 int POLLIN ; 
 int POLLNVAL ; 
 int POLLRDNORM ; 
 int POLLSTANDARD ; 

int
dead_poll(struct vop_poll_args *ap)
{

	if (ap->a_events & ~POLLSTANDARD)
		return (POLLNVAL);

	/*
	 * Let the user find out that the descriptor is gone.
	 */
	return (POLLHUP | ((POLLIN | POLLRDNORM) & ap->a_events));

}