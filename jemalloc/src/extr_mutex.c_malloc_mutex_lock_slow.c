#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  nstime_t ;
struct TYPE_6__ {scalar_t__ max_n_thds; int /*<<< orphan*/  max_wait_time; int /*<<< orphan*/  tot_wait_time; int /*<<< orphan*/  n_wait_times; int /*<<< orphan*/  n_waiting_thds; int /*<<< orphan*/  n_spin_acquired; } ;
typedef  TYPE_1__ mutex_prof_data_t ;
struct TYPE_7__ {int /*<<< orphan*/  locked; TYPE_1__ prof_data; } ;
typedef  TYPE_2__ malloc_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 int MALLOC_MUTEX_MAX_SPIN ; 
 int /*<<< orphan*/  NSTIME_ZERO_INITIALIZER ; 
 scalar_t__ atomic_fetch_add_u32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_fetch_sub_u32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_load_b (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_stats ; 
 int /*<<< orphan*/  malloc_mutex_lock_final (TYPE_2__*) ; 
 int /*<<< orphan*/  malloc_mutex_trylock_final (TYPE_2__*) ; 
 int ncpus ; 
 int /*<<< orphan*/  nstime_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nstime_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nstime_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nstime_subtract (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nstime_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_cpu_spinwait () ; 

void
malloc_mutex_lock_slow(malloc_mutex_t *mutex) {
	mutex_prof_data_t *data = &mutex->prof_data;
	nstime_t before = NSTIME_ZERO_INITIALIZER;

	if (ncpus == 1) {
		goto label_spin_done;
	}

	int cnt = 0, max_cnt = MALLOC_MUTEX_MAX_SPIN;
	do {
		spin_cpu_spinwait();
		if (!atomic_load_b(&mutex->locked, ATOMIC_RELAXED)
                    && !malloc_mutex_trylock_final(mutex)) {
			data->n_spin_acquired++;
			return;
		}
	} while (cnt++ < max_cnt);

	if (!config_stats) {
		/* Only spin is useful when stats is off. */
		malloc_mutex_lock_final(mutex);
		return;
	}
label_spin_done:
	nstime_update(&before);
	/* Copy before to after to avoid clock skews. */
	nstime_t after;
	nstime_copy(&after, &before);
	uint32_t n_thds = atomic_fetch_add_u32(&data->n_waiting_thds, 1,
	    ATOMIC_RELAXED) + 1;
	/* One last try as above two calls may take quite some cycles. */
	if (!malloc_mutex_trylock_final(mutex)) {
		atomic_fetch_sub_u32(&data->n_waiting_thds, 1, ATOMIC_RELAXED);
		data->n_spin_acquired++;
		return;
	}

	/* True slow path. */
	malloc_mutex_lock_final(mutex);
	/* Update more slow-path only counters. */
	atomic_fetch_sub_u32(&data->n_waiting_thds, 1, ATOMIC_RELAXED);
	nstime_update(&after);

	nstime_t delta;
	nstime_copy(&delta, &after);
	nstime_subtract(&delta, &before);

	data->n_wait_times++;
	nstime_add(&data->tot_wait_time, &delta);
	if (nstime_compare(&data->max_wait_time, &delta) < 0) {
		nstime_copy(&data->max_wait_time, &delta);
	}
	if (n_thds > data->max_n_thds) {
		data->max_n_thds = n_thds;
	}
}