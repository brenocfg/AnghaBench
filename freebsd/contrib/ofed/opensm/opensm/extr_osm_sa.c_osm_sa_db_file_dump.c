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
struct TYPE_5__ {scalar_t__ dirty; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_1__ sa; } ;
typedef  TYPE_2__ osm_opensm_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  cl_plock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_plock_release (int /*<<< orphan*/ *) ; 
 int opensm_dump_to_file (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa_dump_all_sa ; 

int osm_sa_db_file_dump(osm_opensm_t * p_osm)
{
	int res = 1;

	cl_plock_acquire(&p_osm->lock);
	if (p_osm->sa.dirty) {
		res = opensm_dump_to_file(
			p_osm, "opensm-sa.dump", sa_dump_all_sa);
		if (!res)
			p_osm->sa.dirty = FALSE;
	}
	cl_plock_release(&p_osm->lock);

	return res;
}