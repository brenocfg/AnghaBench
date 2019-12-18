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
typedef  int /*<<< orphan*/  tsdn_t ;

/* Variables and functions */
 unsigned int PROF_NCTX_LOCKS ; 
 unsigned int PROF_NTDATA_LOCKS ; 
 int /*<<< orphan*/  bt2gctx_mtx ; 
 scalar_t__ config_prof ; 
 int /*<<< orphan*/ * gctx_locks ; 
 int /*<<< orphan*/  malloc_mutex_prefork (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ opt_prof ; 
 int /*<<< orphan*/  prof_dump_mtx ; 
 int /*<<< orphan*/ * tdata_locks ; 
 int /*<<< orphan*/  tdatas_mtx ; 

void
prof_prefork0(tsdn_t *tsdn) {
	if (config_prof && opt_prof) {
		unsigned i;

		malloc_mutex_prefork(tsdn, &prof_dump_mtx);
		malloc_mutex_prefork(tsdn, &bt2gctx_mtx);
		malloc_mutex_prefork(tsdn, &tdatas_mtx);
		for (i = 0; i < PROF_NTDATA_LOCKS; i++) {
			malloc_mutex_prefork(tsdn, &tdata_locks[i]);
		}
		for (i = 0; i < PROF_NCTX_LOCKS; i++) {
			malloc_mutex_prefork(tsdn, &gctx_locks[i]);
		}
	}
}