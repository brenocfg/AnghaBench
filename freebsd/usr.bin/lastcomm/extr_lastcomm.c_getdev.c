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
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 scalar_t__ NODEV ; 
 int /*<<< orphan*/  S_IFCHR ; 
 char* devname (scalar_t__,int /*<<< orphan*/ ) ; 

const char *
getdev(dev_t dev)
{
	static dev_t lastdev = (dev_t)-1;
	static const char *lastname;

	if (dev == NODEV)			/* Special case. */
		return ("__");
	if (dev == lastdev)			/* One-element cache. */
		return (lastname);
	lastdev = dev;
	lastname = devname(dev, S_IFCHR);
	return (lastname);
}