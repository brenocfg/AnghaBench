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
 int /*<<< orphan*/  DELAY (int) ; 
 int RB_POWERCYCLE ; 
 int RB_POWEROFF ; 
 int poweroff_delay ; 

__attribute__((used)) static void
poweroff_wait(void *junk, int howto)
{

	if ((howto & (RB_POWEROFF | RB_POWERCYCLE)) == 0 || poweroff_delay <= 0)
		return;
	DELAY(poweroff_delay * 1000);
}