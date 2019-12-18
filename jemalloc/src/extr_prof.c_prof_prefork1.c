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
 scalar_t__ config_prof ; 
 int /*<<< orphan*/  malloc_mutex_prefork (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_thr_uid_mtx ; 
 scalar_t__ opt_prof ; 
 int /*<<< orphan*/  prof_active_mtx ; 
 int /*<<< orphan*/  prof_dump_filename_mtx ; 
 int /*<<< orphan*/  prof_gdump_mtx ; 
 int /*<<< orphan*/  prof_thread_active_init_mtx ; 

void
prof_prefork1(tsdn_t *tsdn) {
	if (config_prof && opt_prof) {
		malloc_mutex_prefork(tsdn, &prof_active_mtx);
		malloc_mutex_prefork(tsdn, &prof_dump_filename_mtx);
		malloc_mutex_prefork(tsdn, &prof_gdump_mtx);
		malloc_mutex_prefork(tsdn, &next_thr_uid_mtx);
		malloc_mutex_prefork(tsdn, &prof_thread_active_init_mtx);
	}
}