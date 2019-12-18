#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdev_indirect_mapping_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  space_map_t ;
struct TYPE_3__ {int /*<<< orphan*/ * losma_vim; int /*<<< orphan*/ * losma_counts; } ;
typedef  TYPE_1__ load_obsolete_space_map_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_obsolete_sm_callback ; 
 int /*<<< orphan*/  space_map_iterate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

void
vdev_indirect_mapping_load_obsolete_spacemap(vdev_indirect_mapping_t *vim,
    uint32_t *counts, space_map_t *obsolete_space_sm)
{
	load_obsolete_space_map_arg_t losma;
	losma.losma_counts = counts;
	losma.losma_vim = vim;
	VERIFY0(space_map_iterate(obsolete_space_sm,
	    load_obsolete_sm_callback, &losma));
}