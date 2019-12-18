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
 scalar_t__ c_active_brushes ; 
 scalar_t__ c_brushmemory ; 
 scalar_t__ c_nodememory ; 
 scalar_t__ c_nodes ; 
 scalar_t__ c_nonvis ; 
 scalar_t__ c_peak_brushmemory ; 
 scalar_t__ c_peak_totalbspmemory ; 
 scalar_t__ c_solidleafnodes ; 
 scalar_t__ c_totalsides ; 

void ResetBrushBSP(void)
{
	c_nodes = 0;
	c_nonvis = 0;
	c_active_brushes = 0;
	c_solidleafnodes = 0;
	c_totalsides = 0;
	c_brushmemory = 0;
	c_peak_brushmemory = 0;
	c_nodememory = 0;
	c_peak_totalbspmemory = 0;
}