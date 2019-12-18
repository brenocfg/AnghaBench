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
 int HBP_NUM ; 
 int TYPE_DATA ; 

int hw_breakpoint_slots(int type)
{
	if (type == TYPE_DATA)
		return HBP_NUM;
	return 0;		/* no instruction breakpoints available */
}