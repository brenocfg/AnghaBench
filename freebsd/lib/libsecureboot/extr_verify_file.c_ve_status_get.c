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
 int SOPEN_MAX ; 
 int VE_NOT_CHECKED ; 
 scalar_t__ VE_STATUS_VALID ; 
 int* ve_status ; 
 scalar_t__ ve_status_state ; 

int
ve_status_get(int fd)
{
	if (!ve_status_state) {
		return (VE_NOT_CHECKED);
	}
	if (ve_status_state == VE_STATUS_VALID &&
		fd >= 0 && fd < SOPEN_MAX)
		return (ve_status[fd]);
	return (ve_status[SOPEN_MAX]);	/* most recent */
}