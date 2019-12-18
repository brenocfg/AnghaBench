#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_13__ {int td_flags; scalar_t__ td_objset; int /*<<< orphan*/ * td_spa; int /*<<< orphan*/  td_hole_birth_enabled_txg; void* td_realloc_possible; void* td_paused; TYPE_2__* td_pfd; void* td_arg; int /*<<< orphan*/  td_func; int /*<<< orphan*/ * td_resume; scalar_t__ td_min_txg; int /*<<< orphan*/ * td_rootbp; } ;
typedef  TYPE_1__ traverse_data_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_14__ {int pd_flags; int /*<<< orphan*/  pd_cv; int /*<<< orphan*/  pd_mtx; void* pd_exited; void* pd_cancel; int /*<<< orphan*/  pd_resume; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ prefetch_data_t ;
struct TYPE_15__ {int /*<<< orphan*/  os_zil_header; } ;
typedef  TYPE_3__ objset_phys_t ;
struct TYPE_16__ {scalar_t__ ds_object; int /*<<< orphan*/  ds_is_snapshot; } ;
typedef  TYPE_4__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  blkptr_cb_t ;
typedef  int /*<<< orphan*/  arc_flags_t ;
struct TYPE_17__ {TYPE_3__* b_data; } ;
typedef  TYPE_5__ arc_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_FLAG_WAIT ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BP_IS_HOLE (int /*<<< orphan*/ *) ; 
 void* B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  CV_DEFAULT ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  SET_BOOKMARK (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_FEATURE_HOLE_BIRTH ; 
 int /*<<< orphan*/  TQ_NOQUEUE ; 
 int TRAVERSE_POST ; 
 int TRAVERSE_PRE ; 
 int TRAVERSE_PREFETCH_DATA ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZB_ROOT_BLKID ; 
 int /*<<< orphan*/  ZB_ROOT_LEVEL ; 
 int /*<<< orphan*/  ZB_ROOT_OBJECT ; 
 int /*<<< orphan*/  ZIO_FLAG_CANFAIL ; 
 int /*<<< orphan*/  ZIO_PRIORITY_ASYNC_READ ; 
 int /*<<< orphan*/  arc_buf_destroy (TYPE_5__*,TYPE_5__**) ; 
 int /*<<< orphan*/  arc_getbuf_func ; 
 int arc_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_feature_enabled_txg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ spa_feature_is_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_taskq ; 
 scalar_t__ taskq_dispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  traverse_prefetch_thread ; 
 int traverse_visitbp (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  traverse_zil (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
traverse_impl(spa_t *spa, dsl_dataset_t *ds, uint64_t objset, blkptr_t *rootbp,
    uint64_t txg_start, zbookmark_phys_t *resume, int flags,
    blkptr_cb_t func, void *arg)
{
	traverse_data_t td;
	prefetch_data_t pd = { 0 };
	zbookmark_phys_t czb;
	int err;

	ASSERT(ds == NULL || objset == ds->ds_object);
	ASSERT(!(flags & TRAVERSE_PRE) || !(flags & TRAVERSE_POST));

	td.td_spa = spa;
	td.td_objset = objset;
	td.td_rootbp = rootbp;
	td.td_min_txg = txg_start;
	td.td_resume = resume;
	td.td_func = func;
	td.td_arg = arg;
	td.td_pfd = &pd;
	td.td_flags = flags;
	td.td_paused = B_FALSE;
	td.td_realloc_possible = (txg_start == 0 ? B_FALSE : B_TRUE);

	if (spa_feature_is_active(spa, SPA_FEATURE_HOLE_BIRTH)) {
		VERIFY(spa_feature_enabled_txg(spa,
		    SPA_FEATURE_HOLE_BIRTH, &td.td_hole_birth_enabled_txg));
	} else {
		td.td_hole_birth_enabled_txg = UINT64_MAX;
	}

	pd.pd_flags = flags;
	if (resume != NULL)
		pd.pd_resume = *resume;
	mutex_init(&pd.pd_mtx, NULL, MUTEX_DEFAULT, NULL);
	cv_init(&pd.pd_cv, NULL, CV_DEFAULT, NULL);

	/* See comment on ZIL traversal in dsl_scan_visitds. */
	if (ds != NULL && !ds->ds_is_snapshot && !BP_IS_HOLE(rootbp)) {
		arc_flags_t flags = ARC_FLAG_WAIT;
		objset_phys_t *osp;
		arc_buf_t *buf;

		err = arc_read(NULL, td.td_spa, rootbp,
		    arc_getbuf_func, &buf,
		    ZIO_PRIORITY_ASYNC_READ, ZIO_FLAG_CANFAIL, &flags, NULL);
		if (err != 0)
			return (err);

		osp = buf->b_data;
		traverse_zil(&td, &osp->os_zil_header);
		arc_buf_destroy(buf, &buf);
	}

	if (!(flags & TRAVERSE_PREFETCH_DATA) ||
	    0 == taskq_dispatch(system_taskq, traverse_prefetch_thread,
	    &td, TQ_NOQUEUE))
		pd.pd_exited = B_TRUE;

	SET_BOOKMARK(&czb, td.td_objset,
	    ZB_ROOT_OBJECT, ZB_ROOT_LEVEL, ZB_ROOT_BLKID);
	err = traverse_visitbp(&td, NULL, rootbp, &czb);

	mutex_enter(&pd.pd_mtx);
	pd.pd_cancel = B_TRUE;
	cv_broadcast(&pd.pd_cv);
	while (!pd.pd_exited)
		cv_wait(&pd.pd_cv, &pd.pd_mtx);
	mutex_exit(&pd.pd_mtx);

	mutex_destroy(&pd.pd_mtx);
	cv_destroy(&pd.pd_cv);

	return (err);
}