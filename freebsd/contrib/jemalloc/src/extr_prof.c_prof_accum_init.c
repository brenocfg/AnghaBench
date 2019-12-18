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
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_3__ {scalar_t__ accumbytes; int /*<<< orphan*/  mtx; } ;
typedef  TYPE_1__ prof_accum_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 int /*<<< orphan*/  WITNESS_RANK_PROF_ACCUM ; 
 int /*<<< orphan*/  atomic_store_u64 (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_prof ; 
 scalar_t__ malloc_mutex_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_rank_exclusive ; 

bool
prof_accum_init(tsdn_t *tsdn, prof_accum_t *prof_accum) {
	cassert(config_prof);

#ifndef JEMALLOC_ATOMIC_U64
	if (malloc_mutex_init(&prof_accum->mtx, "prof_accum",
	    WITNESS_RANK_PROF_ACCUM, malloc_mutex_rank_exclusive)) {
		return true;
	}
	prof_accum->accumbytes = 0;
#else
	atomic_store_u64(&prof_accum->accumbytes, 0, ATOMIC_RELAXED);
#endif
	return false;
}