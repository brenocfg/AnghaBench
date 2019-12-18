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
struct netmap_mem_d {int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int NM_DEBUG_MEM ; 
 int netmap_debug ; 
 int /*<<< orphan*/  nm_prinf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
netmap_mem2_deref(struct netmap_mem_d *nmd)
{

	if (netmap_debug & NM_DEBUG_MEM)
		nm_prinf("active = %d", nmd->active);

}