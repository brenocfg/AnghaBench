#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* sm_phys; TYPE_1__* sm_dbuf; } ;
typedef  TYPE_3__ space_map_t ;
typedef  int /*<<< orphan*/  space_map_phys_t ;
struct TYPE_6__ {int /*<<< orphan*/  smp_histogram; } ;
struct TYPE_5__ {int db_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 

void
space_map_histogram_clear(space_map_t *sm)
{
	if (sm->sm_dbuf->db_size != sizeof (space_map_phys_t))
		return;

	bzero(sm->sm_phys->smp_histogram, sizeof (sm->sm_phys->smp_histogram));
}