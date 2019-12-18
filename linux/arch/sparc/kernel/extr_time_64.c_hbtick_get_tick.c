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
 unsigned long long TICK_PRIV_BIT ; 
 unsigned long long __hbird_read_stick () ; 

__attribute__((used)) static unsigned long long hbtick_get_tick(void)
{
	return __hbird_read_stick() & ~TICK_PRIV_BIT;
}