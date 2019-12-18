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
 int RT_MAXFIBS ; 
 int rt_numfibs ; 

__attribute__((used)) static void
route_init(void)
{

	/* whack the tunable ints into  line. */
	if (rt_numfibs > RT_MAXFIBS)
		rt_numfibs = RT_MAXFIBS;
	if (rt_numfibs == 0)
		rt_numfibs = 1;
}