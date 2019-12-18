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
 int POLLIN ; 
 int POLLNVAL ; 
 int POLLOUT ; 
 int POLLRDNORM ; 
 int POLLSTANDARD ; 
 int POLLWRNORM ; 

int
poll_no_poll(int events)
{
	/*
	 * Return true for read/write.  If the user asked for something
	 * special, return POLLNVAL, so that clients have a way of
	 * determining reliably whether or not the extended
	 * functionality is present without hard-coding knowledge
	 * of specific filesystem implementations.
	 */
	if (events & ~POLLSTANDARD)
		return (POLLNVAL);

	return (events & (POLLIN | POLLOUT | POLLRDNORM | POLLWRNORM));
}