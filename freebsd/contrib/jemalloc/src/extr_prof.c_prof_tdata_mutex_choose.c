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
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  malloc_mutex_t ;

/* Variables and functions */
 size_t PROF_NTDATA_LOCKS ; 
 int /*<<< orphan*/ * tdata_locks ; 

__attribute__((used)) static malloc_mutex_t *
prof_tdata_mutex_choose(uint64_t thr_uid) {
	return &tdata_locks[thr_uid % PROF_NTDATA_LOCKS];
}