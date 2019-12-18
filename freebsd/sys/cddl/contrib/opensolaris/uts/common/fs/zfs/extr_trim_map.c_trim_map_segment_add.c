#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_15__ {scalar_t__ ts_start; scalar_t__ ts_end; void* ts_time; scalar_t__ ts_txg; } ;
typedef  TYPE_1__ trim_seg_t ;
struct TYPE_16__ {int /*<<< orphan*/  tm_queued_frees; int /*<<< orphan*/  tm_lock; } ;
typedef  TYPE_2__ trim_map_t ;
typedef  void* hrtime_t ;
typedef  int boolean_t ;
typedef  int /*<<< orphan*/  avl_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVL_AFTER ; 
 int /*<<< orphan*/  AVL_BEFORE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRIM_MAP_ADD (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  TRIM_MAP_REM (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 TYPE_1__* avl_find (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_insert (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* avl_nearest (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avl_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 
 void* gethrtime () ; 
 TYPE_1__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 

__attribute__((used)) static void
trim_map_segment_add(trim_map_t *tm, uint64_t start, uint64_t end, uint64_t txg)
{
	avl_index_t where;
	trim_seg_t tsearch, *ts_before, *ts_after, *ts;
	boolean_t merge_before, merge_after;
	hrtime_t time;

	ASSERT(MUTEX_HELD(&tm->tm_lock));
	VERIFY(start < end);

	time = gethrtime();
	tsearch.ts_start = start;
	tsearch.ts_end = end;

	ts = avl_find(&tm->tm_queued_frees, &tsearch, &where);
	if (ts != NULL) {
		if (start < ts->ts_start)
			trim_map_segment_add(tm, start, ts->ts_start, txg);
		if (end > ts->ts_end)
			trim_map_segment_add(tm, ts->ts_end, end, txg);
		return;
	}

	ts_before = avl_nearest(&tm->tm_queued_frees, where, AVL_BEFORE);
	ts_after = avl_nearest(&tm->tm_queued_frees, where, AVL_AFTER);

	merge_before = (ts_before != NULL && ts_before->ts_end == start);
	merge_after = (ts_after != NULL && ts_after->ts_start == end);

	if (merge_before && merge_after) {
		avl_remove(&tm->tm_queued_frees, ts_before);
		TRIM_MAP_REM(tm, ts_before);
		TRIM_MAP_REM(tm, ts_after);
		ts_after->ts_start = ts_before->ts_start;
		ts_after->ts_txg = txg;
		ts_after->ts_time = time;
		TRIM_MAP_ADD(tm, ts_after);
		kmem_free(ts_before, sizeof (*ts_before));
	} else if (merge_before) {
		TRIM_MAP_REM(tm, ts_before);
		ts_before->ts_end = end;
		ts_before->ts_txg = txg;
		ts_before->ts_time = time;
		TRIM_MAP_ADD(tm, ts_before);
	} else if (merge_after) {
		TRIM_MAP_REM(tm, ts_after);
		ts_after->ts_start = start;
		ts_after->ts_txg = txg;
		ts_after->ts_time = time;
		TRIM_MAP_ADD(tm, ts_after);
	} else {
		ts = kmem_alloc(sizeof (*ts), KM_SLEEP);
		ts->ts_start = start;
		ts->ts_end = end;
		ts->ts_txg = txg;
		ts->ts_time = time;
		avl_insert(&tm->tm_queued_frees, ts, where);
		TRIM_MAP_ADD(tm, ts);
	}
}