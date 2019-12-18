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
typedef  int /*<<< orphan*/  tsd_t ;

/* Variables and functions */
 int DUMP_FILENAME_BUFSIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_prof ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opt_prof ; 
 char* opt_prof_prefix ; 
 int /*<<< orphan*/  prof_booted ; 
 int prof_dump (int /*<<< orphan*/ *,int,char const*,int) ; 
 int /*<<< orphan*/  prof_dump_filename (char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prof_dump_mseq ; 
 int /*<<< orphan*/  prof_dump_seq_mtx ; 
 scalar_t__ tsd_reentrancy_level_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

bool
prof_mdump(tsd_t *tsd, const char *filename) {
	cassert(config_prof);
	assert(tsd_reentrancy_level_get(tsd) == 0);

	if (!opt_prof || !prof_booted) {
		return true;
	}
	char filename_buf[DUMP_FILENAME_BUFSIZE];
	if (filename == NULL) {
		/* No filename specified, so automatically generate one. */
		if (opt_prof_prefix[0] == '\0') {
			return true;
		}
		malloc_mutex_lock(tsd_tsdn(tsd), &prof_dump_seq_mtx);
		prof_dump_filename(filename_buf, 'm', prof_dump_mseq);
		prof_dump_mseq++;
		malloc_mutex_unlock(tsd_tsdn(tsd), &prof_dump_seq_mtx);
		filename = filename_buf;
	}
	return prof_dump(tsd, true, filename, false);
}