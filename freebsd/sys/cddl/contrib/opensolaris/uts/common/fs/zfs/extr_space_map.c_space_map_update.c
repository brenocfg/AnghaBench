#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* sm_phys; int /*<<< orphan*/  sm_length; int /*<<< orphan*/  sm_alloc; } ;
typedef  TYPE_2__ space_map_t ;
struct TYPE_4__ {int /*<<< orphan*/  smp_objsize; int /*<<< orphan*/  smp_alloc; } ;

/* Variables and functions */

void
space_map_update(space_map_t *sm)
{
	if (sm == NULL)
		return;

	sm->sm_alloc = sm->sm_phys->smp_alloc;
	sm->sm_length = sm->sm_phys->smp_objsize;
}