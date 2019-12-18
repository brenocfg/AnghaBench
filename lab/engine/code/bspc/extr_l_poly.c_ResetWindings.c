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
 scalar_t__ c_active_windings ; 
 scalar_t__ c_peak_windingmemory ; 
 scalar_t__ c_peak_windings ; 
 scalar_t__ c_winding_allocs ; 
 scalar_t__ c_winding_points ; 
 scalar_t__ c_windingmemory ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  windingerror ; 

void ResetWindings(void)
{
	c_active_windings = 0;
	c_peak_windings = 0;
	c_winding_allocs = 0;
	c_winding_points = 0;
	c_windingmemory = 0;
	c_peak_windingmemory = 0;

	strcpy(windingerror, "");
}