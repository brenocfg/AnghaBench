#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ vdev_initialize_inflight; int /*<<< orphan*/  vdev_initialize_lock; int /*<<< orphan*/  vdev_initialize_cv; int /*<<< orphan*/ * vdev_initialize_thread; int /*<<< orphan*/  vdev_initialize_exit_wanted; int /*<<< orphan*/ * vdev_initialize_tree; int /*<<< orphan*/  vdev_initialize_io_lock; int /*<<< orphan*/  vdev_initialize_io_cv; TYPE_1__* vdev_top; int /*<<< orphan*/  vdev_detached; scalar_t__ vdev_initialize_last_offset; int /*<<< orphan*/ * vdev_spa; } ;
typedef  TYPE_2__ vdev_t ;
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_16__ {int /*<<< orphan*/  ms_lock; int /*<<< orphan*/  ms_allocatable; } ;
typedef  TYPE_3__ metaslab_t ;
typedef  int /*<<< orphan*/  abd_t ;
struct TYPE_14__ {size_t vdev_ms_count; TYPE_3__** vdev_ms; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_CONFIG ; 
 int /*<<< orphan*/  VDEV_INITIALIZE_COMPLETE ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  metaslab_load (TYPE_3__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * range_tree_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_tree_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_tree_vacate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_tree_walk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  spa_config_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_get_dsl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_exit () ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vdev_initialize_block_alloc () ; 
 int /*<<< orphan*/  vdev_initialize_block_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_initialize_calculate_progress (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_initialize_change_state (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_initialize_load (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_initialize_ms_mark (TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_initialize_ms_unmark (TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_initialize_range_add ; 
 int vdev_initialize_ranges (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int vdev_is_concrete (TYPE_2__*) ; 
 scalar_t__ vdev_writeable (TYPE_2__*) ; 

__attribute__((used)) static void
vdev_initialize_thread(void *arg)
{
	vdev_t *vd = arg;
	spa_t *spa = vd->vdev_spa;
	int error = 0;
	uint64_t ms_count = 0;

	ASSERT(vdev_is_concrete(vd));
	spa_config_enter(spa, SCL_CONFIG, FTAG, RW_READER);

	vd->vdev_initialize_last_offset = 0;
	vdev_initialize_load(vd);

	abd_t *deadbeef = vdev_initialize_block_alloc();

	vd->vdev_initialize_tree = range_tree_create(NULL, NULL);

	for (uint64_t i = 0; !vd->vdev_detached &&
	    i < vd->vdev_top->vdev_ms_count; i++) {
		metaslab_t *msp = vd->vdev_top->vdev_ms[i];

		/*
		 * If we've expanded the top-level vdev or it's our
		 * first pass, calculate our progress.
		 */
		if (vd->vdev_top->vdev_ms_count != ms_count) {
			vdev_initialize_calculate_progress(vd);
			ms_count = vd->vdev_top->vdev_ms_count;
		}

		vdev_initialize_ms_mark(msp);
		mutex_enter(&msp->ms_lock);
		VERIFY0(metaslab_load(msp));

		range_tree_walk(msp->ms_allocatable, vdev_initialize_range_add,
		    vd);
		mutex_exit(&msp->ms_lock);

		spa_config_exit(spa, SCL_CONFIG, FTAG);
		error = vdev_initialize_ranges(vd, deadbeef);
		vdev_initialize_ms_unmark(msp);
		spa_config_enter(spa, SCL_CONFIG, FTAG, RW_READER);

		range_tree_vacate(vd->vdev_initialize_tree, NULL, NULL);
		if (error != 0)
			break;
	}

	spa_config_exit(spa, SCL_CONFIG, FTAG);
	mutex_enter(&vd->vdev_initialize_io_lock);
	while (vd->vdev_initialize_inflight > 0) {
		cv_wait(&vd->vdev_initialize_io_cv,
		    &vd->vdev_initialize_io_lock);
	}
	mutex_exit(&vd->vdev_initialize_io_lock);

	range_tree_destroy(vd->vdev_initialize_tree);
	vdev_initialize_block_free(deadbeef);
	vd->vdev_initialize_tree = NULL;

	mutex_enter(&vd->vdev_initialize_lock);
	if (!vd->vdev_initialize_exit_wanted && vdev_writeable(vd)) {
		vdev_initialize_change_state(vd, VDEV_INITIALIZE_COMPLETE);
	}
	ASSERT(vd->vdev_initialize_thread != NULL ||
	    vd->vdev_initialize_inflight == 0);

	/*
	 * Drop the vdev_initialize_lock while we sync out the
	 * txg since it's possible that a device might be trying to
	 * come online and must check to see if it needs to restart an
	 * initialization. That thread will be holding the spa_config_lock
	 * which would prevent the txg_wait_synced from completing.
	 */
	mutex_exit(&vd->vdev_initialize_lock);
	txg_wait_synced(spa_get_dsl(spa), 0);
	mutex_enter(&vd->vdev_initialize_lock);

	vd->vdev_initialize_thread = NULL;
	cv_broadcast(&vd->vdev_initialize_cv);
	mutex_exit(&vd->vdev_initialize_lock);
	thread_exit();
}