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
 int /*<<< orphan*/  printf (char*) ; 
 int xmon_on ; 

__attribute__((used)) static inline void force_enable_xmon(void)
{
	/* Enable xmon hooks if needed */
	if (!xmon_on) {
		printf("xmon: Enabling debugger hooks\n");
		xmon_on = 1;
	}
}