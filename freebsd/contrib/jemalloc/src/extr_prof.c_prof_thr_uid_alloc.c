#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  tsdn_t ;

/* Variables and functions */
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_thr_uid ; 
 int /*<<< orphan*/  next_thr_uid_mtx ; 

__attribute__((used)) static uint64_t
prof_thr_uid_alloc(tsdn_t *tsdn) {
	uint64_t thr_uid;

	malloc_mutex_lock(tsdn, &next_thr_uid_mtx);
	thr_uid = next_thr_uid;
	next_thr_uid++;
	malloc_mutex_unlock(tsdn, &next_thr_uid_mtx);

	return thr_uid;
}