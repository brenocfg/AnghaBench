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
 int PROF_DUMP_FILENAME_LEN ; 
 int /*<<< orphan*/  QUANTUM ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b0get () ; 
 char* base_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_prof ; 
 int /*<<< orphan*/  ctl_mtx_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_dump_filename_mtx ; 
 char* prof_dump_prefix ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

bool
prof_dump_prefix_set(tsdn_t *tsdn, const char *prefix) {
	cassert(config_prof);
	ctl_mtx_assert_held(tsdn);
	malloc_mutex_lock(tsdn, &prof_dump_filename_mtx);
	if (prof_dump_prefix == NULL) {
		malloc_mutex_unlock(tsdn, &prof_dump_filename_mtx);
		/* Everything is still guarded by ctl_mtx. */
		char *buffer = base_alloc(tsdn, b0get(), PROF_DUMP_FILENAME_LEN,
		    QUANTUM);
		if (buffer == NULL) {
			return true;
		}
		malloc_mutex_lock(tsdn, &prof_dump_filename_mtx);
		prof_dump_prefix = buffer;
	}
	assert(prof_dump_prefix != NULL);

	strncpy(prof_dump_prefix, prefix, PROF_DUMP_FILENAME_LEN - 1);
	prof_dump_prefix[PROF_DUMP_FILENAME_LEN - 1] = '\0';
	malloc_mutex_unlock(tsdn, &prof_dump_filename_mtx);

	return false;
}