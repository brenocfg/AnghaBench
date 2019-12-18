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
 int TIME_T_BITS_IN_FILE ; 
 int max_time ; 
 int min_time ; 

__attribute__((used)) static void
setboundaries (void)
{
	register int	i;

	min_time = -1;
	for (i = 0; i < TIME_T_BITS_IN_FILE - 1; ++i)
		min_time *= 2;
	max_time = -(min_time + 1);
}