#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
typedef  int /*<<< orphan*/ * flash_slicer_t ;
struct TYPE_2__ {int /*<<< orphan*/ * slicer; } ;

/* Variables and functions */
 int TRUE ; 
 TYPE_1__* g_flashmap_slicers ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 

void flash_register_slicer(flash_slicer_t slicer, u_int type, bool force)
{

	g_topology_lock();
	if (g_flashmap_slicers[type].slicer == NULL || force == TRUE)
		g_flashmap_slicers[type].slicer = slicer;
	g_topology_unlock();
}