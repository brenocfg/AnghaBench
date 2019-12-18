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
 scalar_t__ PROF_DUMP_FILENAME_LEN ; 
 int /*<<< orphan*/  log_filename ; 
 int /*<<< orphan*/  log_mtx ; 
 int /*<<< orphan*/  log_seq ; 
 int /*<<< orphan*/  log_start_timestamp ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nstime_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opt_prof ; 
 int /*<<< orphan*/  prof_booted ; 
 int /*<<< orphan*/  prof_get_default_filename (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ prof_logging_state ; 
 scalar_t__ prof_logging_state_started ; 
 scalar_t__ prof_logging_state_stopped ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

bool
prof_log_start(tsdn_t *tsdn, const char *filename) {
	if (!opt_prof || !prof_booted) {
		return true;
	}

	bool ret = false;

	malloc_mutex_lock(tsdn, &log_mtx);

	if (prof_logging_state != prof_logging_state_stopped) {
		ret = true;
	} else if (filename == NULL) {
		/* Make default name. */
		prof_get_default_filename(tsdn, log_filename, log_seq);
		log_seq++;
		prof_logging_state = prof_logging_state_started;
	} else if (strlen(filename) >= PROF_DUMP_FILENAME_LEN) {
		ret = true;
	} else {
		strcpy(log_filename, filename);
		prof_logging_state = prof_logging_state_started;
	}

	if (!ret) {
		nstime_update(&log_start_timestamp);
	}

	malloc_mutex_unlock(tsdn, &log_mtx);

	return ret;
}