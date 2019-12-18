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
 long H_BUSY ; 
 scalar_t__ H_IS_LONG_BUSY (long) ; 
 unsigned int get_longbusy_msecs (long) ; 

__attribute__((used)) static unsigned int plpar_busy_delay_time(long rc)
{
	unsigned int ms = 0;

	if (H_IS_LONG_BUSY(rc)) {
		ms = get_longbusy_msecs(rc);
	} else if (rc == H_BUSY) {
		ms = 10; /* seems appropriate for XIVE hcalls */
	}

	return ms;
}