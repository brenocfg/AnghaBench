#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* sm_phys; int /*<<< orphan*/ * sm_dbuf; } ;
typedef  TYPE_2__ space_map_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {scalar_t__ smp_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ space_map_allocated (TYPE_2__*) ; 

int64_t
space_map_alloc_delta(space_map_t *sm)
{
	if (sm == NULL)
		return (0);
	ASSERT(sm->sm_dbuf != NULL);
	return (sm->sm_phys->smp_alloc - space_map_allocated(sm));
}