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
 int /*<<< orphan*/  clksrc ; 
 unsigned long tc_get_cycles (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long tc_delay_timer_read(void)
{
	return tc_get_cycles(&clksrc);
}