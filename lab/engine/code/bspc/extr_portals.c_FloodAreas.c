#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  headnode; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  FindAreas_r (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Log_Print (char*,...) ; 
 int /*<<< orphan*/  SetAreaPortalAreas_r (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_areas ; 

void FloodAreas (tree_t *tree)
{
	Log_Print("--- FloodAreas ---\n");
	FindAreas_r (tree->headnode);
	SetAreaPortalAreas_r (tree->headnode);
	Log_Print("%5i areas\n", c_areas);
}