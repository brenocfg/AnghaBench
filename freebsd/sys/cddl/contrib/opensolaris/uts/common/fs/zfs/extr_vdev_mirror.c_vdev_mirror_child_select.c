#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ io_txg; int /*<<< orphan*/ * io_bp; TYPE_2__* io_vsd; } ;
typedef  TYPE_1__ zio_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_9__ {size_t mm_preferred_cnt; int mm_children; int* mm_preferred; TYPE_3__* mm_child; } ;
typedef  TYPE_2__ mirror_map_t ;
struct TYPE_10__ {int mc_tried; int mc_skipped; int mc_speculative; int mc_load; int /*<<< orphan*/  mc_vd; int /*<<< orphan*/  mc_offset; void* mc_error; } ;
typedef  TYPE_3__ mirror_child_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BP_PHYSICAL_BIRTH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DTL_MISSING ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  ESTALE ; 
 int INT_MAX ; 
 void* SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ vdev_dtl_contains (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int vdev_mirror_load (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vdev_mirror_preferred_child_randomize (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_queue_register_lastoffset (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_readable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vdev_mirror_child_select(zio_t *zio)
{
	mirror_map_t *mm = zio->io_vsd;
	uint64_t txg = zio->io_txg;
	int c, lowest_load;

	ASSERT(zio->io_bp == NULL || BP_PHYSICAL_BIRTH(zio->io_bp) == txg);

	lowest_load = INT_MAX;
	mm->mm_preferred_cnt = 0;
	for (c = 0; c < mm->mm_children; c++) {
		mirror_child_t *mc;

		mc = &mm->mm_child[c];
		if (mc->mc_tried || mc->mc_skipped)
			continue;

		if (!vdev_readable(mc->mc_vd)) {
			mc->mc_error = SET_ERROR(ENXIO);
			mc->mc_tried = 1;	/* don't even try */
			mc->mc_skipped = 1;
			continue;
		}

		if (vdev_dtl_contains(mc->mc_vd, DTL_MISSING, txg, 1)) {
			mc->mc_error = SET_ERROR(ESTALE);
			mc->mc_skipped = 1;
			mc->mc_speculative = 1;
			continue;
		}

		mc->mc_load = vdev_mirror_load(mm, mc->mc_vd, mc->mc_offset);
		if (mc->mc_load > lowest_load)
			continue;

		if (mc->mc_load < lowest_load) {
			lowest_load = mc->mc_load;
			mm->mm_preferred_cnt = 0;
		}
		mm->mm_preferred[mm->mm_preferred_cnt] = c;
		mm->mm_preferred_cnt++;
	}

	if (mm->mm_preferred_cnt == 1) {
		vdev_queue_register_lastoffset(
		    mm->mm_child[mm->mm_preferred[0]].mc_vd, zio);
		return (mm->mm_preferred[0]);
	}

	if (mm->mm_preferred_cnt > 1) {
		int c = vdev_mirror_preferred_child_randomize(zio);

		vdev_queue_register_lastoffset(mm->mm_child[c].mc_vd, zio);
		return (c);
	}

	/*
	 * Every device is either missing or has this txg in its DTL.
	 * Look for any child we haven't already tried before giving up.
	 */
	for (c = 0; c < mm->mm_children; c++) {
		if (!mm->mm_child[c].mc_tried) {
			vdev_queue_register_lastoffset(mm->mm_child[c].mc_vd,
			    zio);
			return (c);
		}
	}

	/*
	 * Every child failed.  There's no place left to look.
	 */
	return (-1);
}