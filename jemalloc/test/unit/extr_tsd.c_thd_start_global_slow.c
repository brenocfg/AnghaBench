#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_2__ {int /*<<< orphan*/  phase; int /*<<< orphan*/  error; } ;
typedef  TYPE_1__ global_slow_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_SEQ_CST ; 
 int atomic_load_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store_b (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store_u32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mallocx (int,int /*<<< orphan*/ ) ; 
 scalar_t__ originally_fast ; 
 int tsd_fast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tsd_fetch () ; 

__attribute__((used)) static void *
thd_start_global_slow(void *arg) {
	/* PHASE 0 */
	global_slow_data_t *data = (global_slow_data_t *)arg;
	free(mallocx(1, 0));

	tsd_t *tsd = tsd_fetch();
	/*
	 * No global slowness has happened yet; there was an error if we were
	 * originally fast but aren't now.
	 */
	atomic_store_b(&data->error, originally_fast && !tsd_fast(tsd),
	    ATOMIC_SEQ_CST);
	atomic_store_u32(&data->phase, 1, ATOMIC_SEQ_CST);

	/* PHASE 2 */
	while (atomic_load_u32(&data->phase, ATOMIC_SEQ_CST) != 2) {
	}
	free(mallocx(1, 0));
	atomic_store_b(&data->error, tsd_fast(tsd), ATOMIC_SEQ_CST);
	atomic_store_u32(&data->phase, 3, ATOMIC_SEQ_CST);

	/* PHASE 4 */
	while (atomic_load_u32(&data->phase, ATOMIC_SEQ_CST) != 4) {
	}
	free(mallocx(1, 0));
	atomic_store_b(&data->error, tsd_fast(tsd), ATOMIC_SEQ_CST);
	atomic_store_u32(&data->phase, 5, ATOMIC_SEQ_CST);

	/* PHASE 6 */
	while (atomic_load_u32(&data->phase, ATOMIC_SEQ_CST) != 6) {
	}
	free(mallocx(1, 0));
	/* Only one decrement so far. */
	atomic_store_b(&data->error, tsd_fast(tsd), ATOMIC_SEQ_CST);
	atomic_store_u32(&data->phase, 7, ATOMIC_SEQ_CST);

	/* PHASE 8 */
	while (atomic_load_u32(&data->phase, ATOMIC_SEQ_CST) != 8) {
	}
	free(mallocx(1, 0));
	/*
	 * Both decrements happened; we should be fast again (if we ever
	 * were)
	 */
	atomic_store_b(&data->error, originally_fast && !tsd_fast(tsd),
	    ATOMIC_SEQ_CST);
	atomic_store_u32(&data->phase, 9, ATOMIC_SEQ_CST);

	return NULL;
}