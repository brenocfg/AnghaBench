#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_5__ {scalar_t__ ds_reserved; scalar_t__ ds_quota; int /*<<< orphan*/  ds_bp_rwlock; int /*<<< orphan*/  ds_dir; } ;
typedef  TYPE_1__ dsl_dataset_t ;
struct TYPE_6__ {scalar_t__ ds_referenced_bytes; scalar_t__ ds_unique_bytes; int /*<<< orphan*/  ds_bp; } ;

/* Variables and functions */
 scalar_t__ BP_GET_FILL (int /*<<< orphan*/ *) ; 
 scalar_t__ DN_MAX_OBJECT ; 
 int /*<<< orphan*/  FTAG ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* dsl_dataset_phys (TYPE_1__*) ; 
 scalar_t__ dsl_dir_space_available (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrw_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
dsl_dataset_space(dsl_dataset_t *ds,
    uint64_t *refdbytesp, uint64_t *availbytesp,
    uint64_t *usedobjsp, uint64_t *availobjsp)
{
	*refdbytesp = dsl_dataset_phys(ds)->ds_referenced_bytes;
	*availbytesp = dsl_dir_space_available(ds->ds_dir, NULL, 0, TRUE);
	if (ds->ds_reserved > dsl_dataset_phys(ds)->ds_unique_bytes)
		*availbytesp +=
		    ds->ds_reserved - dsl_dataset_phys(ds)->ds_unique_bytes;
	if (ds->ds_quota != 0) {
		/*
		 * Adjust available bytes according to refquota
		 */
		if (*refdbytesp < ds->ds_quota)
			*availbytesp = MIN(*availbytesp,
			    ds->ds_quota - *refdbytesp);
		else
			*availbytesp = 0;
	}
	rrw_enter(&ds->ds_bp_rwlock, RW_READER, FTAG);
	*usedobjsp = BP_GET_FILL(&dsl_dataset_phys(ds)->ds_bp);
	rrw_exit(&ds->ds_bp_rwlock, FTAG);
	*availobjsp = DN_MAX_OBJECT - *usedobjsp;
}