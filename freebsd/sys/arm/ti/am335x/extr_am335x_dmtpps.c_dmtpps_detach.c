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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EBUSY ; 

__attribute__((used)) static int
dmtpps_detach(device_t dev)
{

	/*
	 * There is no way to remove a timecounter once it has been registered,
	 * even if it's not in use, so we can never detach.  If we were
	 * dynamically loaded as a module this will prevent unloading.
	 */
	return (EBUSY);
}