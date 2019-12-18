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
 int /*<<< orphan*/  VE_STATUS_VALID ; 
 int* ve_status ; 
 int /*<<< orphan*/  ve_status_state ; 

__attribute__((used)) static void
ve_status_set(int fd, int ves)
{
	if (fd >= 0 && fd < SOPEN_MAX) {
		ve_status[fd] = ves;
		ve_status_state = VE_STATUS_VALID;
	}
	ve_status[SOPEN_MAX] = ves;
}