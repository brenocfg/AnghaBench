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
 int /*<<< orphan*/  VSEQ_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_prof ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int opt_prof_final ; 
 int /*<<< orphan*/  opt_prof_leak ; 
 char* opt_prof_prefix ; 
 int /*<<< orphan*/  prof_booted ; 
 int /*<<< orphan*/  prof_dump (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prof_dump_filename (char*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prof_dump_seq_mtx ; 
 int /*<<< orphan*/ * tsd_fetch () ; 
 scalar_t__ tsd_reentrancy_level_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
prof_fdump(void) {
	tsd_t *tsd;
	char filename[DUMP_FILENAME_BUFSIZE];

	cassert(config_prof);
	assert(opt_prof_final);
	assert(opt_prof_prefix[0] != '\0');

	if (!prof_booted) {
		return;
	}
	tsd = tsd_fetch();
	assert(tsd_reentrancy_level_get(tsd) == 0);

	malloc_mutex_lock(tsd_tsdn(tsd), &prof_dump_seq_mtx);
	prof_dump_filename(filename, 'f', VSEQ_INVALID);
	malloc_mutex_unlock(tsd_tsdn(tsd), &prof_dump_seq_mtx);
	prof_dump(tsd, false, filename, opt_prof_leak);
}