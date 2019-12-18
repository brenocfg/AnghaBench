#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {scalar_t__ ds_reserved; scalar_t__ ds_quota; int /*<<< orphan*/  ds_dir; } ;
typedef  TYPE_1__ dsl_dataset_t ;
struct TYPE_7__ {scalar_t__ ds_unique_bytes; } ;

/* Variables and functions */
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__* dsl_dataset_phys (TYPE_1__*) ; 
 scalar_t__ dsl_dir_space_available (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dsl_get_referenced (TYPE_1__*) ; 

uint64_t
dsl_get_available(dsl_dataset_t *ds)
{
	uint64_t refdbytes = dsl_get_referenced(ds);
	uint64_t availbytes = dsl_dir_space_available(ds->ds_dir,
	    NULL, 0, TRUE);
	if (ds->ds_reserved > dsl_dataset_phys(ds)->ds_unique_bytes) {
		availbytes +=
		    ds->ds_reserved - dsl_dataset_phys(ds)->ds_unique_bytes;
	}
	if (ds->ds_quota != 0) {
		/*
		 * Adjust available bytes according to refquota
		 */
		if (refdbytes < ds->ds_quota) {
			availbytes = MIN(availbytes,
			    ds->ds_quota - refdbytes);
		} else {
			availbytes = 0;
		}
	}
	return (availbytes);
}