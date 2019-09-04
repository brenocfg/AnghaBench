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
typedef  int /*<<< orphan*/  node_t ;

/* Variables and functions */
 int /*<<< orphan*/  FillOutside_r (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Log_Print (char*,...) ; 
 scalar_t__ c_inside ; 
 scalar_t__ c_outside ; 
 scalar_t__ c_solid ; 

void FillOutside (node_t *headnode)
{
	c_outside = 0;
	c_inside = 0;
	c_solid = 0;
	Log_Print("------- FillOutside --------\n");
	FillOutside_r (headnode);
	Log_Print("%5i solid leaves\n", c_solid);
	Log_Print("%5i leaves filled\n", c_outside);
	Log_Print("%5i inside leaves\n", c_inside);
}