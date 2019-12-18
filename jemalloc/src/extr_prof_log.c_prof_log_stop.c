#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  tsd_t ;
struct prof_emitter_cb_arg_s {int fd; int ret; } ;
typedef  int /*<<< orphan*/  emitter_t ;
struct TYPE_4__ {char* member_2; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; struct prof_emitter_cb_arg_s* member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ buf_writer_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROF_LOG_STOP_BUFSIZE ; 
 int /*<<< orphan*/  TSDN_NULL ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  arena_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  buf_writer_flush (TYPE_1__*) ; 
 int /*<<< orphan*/  buffered_write_cb ; 
 int /*<<< orphan*/  ckh_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ close (int) ; 
 int creat (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emitter_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  emitter_output_json_compact ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ iallocztm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  idalloctm (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * log_alloc_first ; 
 int /*<<< orphan*/ * log_alloc_last ; 
 int /*<<< orphan*/ * log_bt_first ; 
 scalar_t__ log_bt_index ; 
 int /*<<< orphan*/ * log_bt_last ; 
 int /*<<< orphan*/  log_bt_node_set ; 
 int /*<<< orphan*/  log_filename ; 
 int /*<<< orphan*/  log_mtx ; 
 int log_tables_initialized ; 
 int /*<<< orphan*/ * log_thr_first ; 
 scalar_t__ log_thr_index ; 
 int /*<<< orphan*/ * log_thr_last ; 
 int /*<<< orphan*/  log_thr_node_set ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ opt_abort ; 
 int /*<<< orphan*/  opt_prof ; 
 int /*<<< orphan*/  prof_booted ; 
 int /*<<< orphan*/  prof_emitter_write_cb ; 
 scalar_t__ prof_log_dummy ; 
 int /*<<< orphan*/  prof_log_emit_allocs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_log_emit_metadata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_log_emit_threads (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_log_emit_traces (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ prof_logging_state ; 
 scalar_t__ prof_logging_state_dumping ; 
 scalar_t__ prof_logging_state_started ; 
 scalar_t__ prof_logging_state_stopped ; 
 int /*<<< orphan*/  sz_size2index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tsdn_tsd (int /*<<< orphan*/ *) ; 

bool
prof_log_stop(tsdn_t *tsdn) {
	if (!opt_prof || !prof_booted) {
		return true;
	}

	tsd_t *tsd = tsdn_tsd(tsdn);
	malloc_mutex_lock(tsdn, &log_mtx);

	if (prof_logging_state != prof_logging_state_started) {
		malloc_mutex_unlock(tsdn, &log_mtx);
		return true;
	}

	/*
	 * Set the state to dumping. We'll set it to stopped when we're done.
	 * Since other threads won't be able to start/stop/log when the state is
	 * dumping, we don't have to hold the lock during the whole method.
	 */
	prof_logging_state = prof_logging_state_dumping;
	malloc_mutex_unlock(tsdn, &log_mtx);


	emitter_t emitter;

	/* Create a file. */

	int fd;
#ifdef JEMALLOC_JET
	if (prof_log_dummy) {
		fd = 0;
	} else {
		fd = creat(log_filename, 0644);
	}
#else
	fd = creat(log_filename, 0644);
#endif

	if (fd == -1) {
		malloc_printf("<jemalloc>: creat() for log file \"%s\" "
			      " failed with %d\n", log_filename, errno);
		if (opt_abort) {
			abort();
		}
		return true;
	}

	struct prof_emitter_cb_arg_s arg;
	arg.fd = fd;

	char *prof_log_stop_buf = (char *)iallocztm(tsdn,
	    PROF_LOG_STOP_BUFSIZE, sz_size2index(PROF_LOG_STOP_BUFSIZE),
	    false, NULL, true, arena_get(TSDN_NULL, 0, true), true);
	buf_writer_arg_t prof_log_stop_buf_arg = {prof_emitter_write_cb, &arg,
	    prof_log_stop_buf, PROF_LOG_STOP_BUFSIZE - 1, 0};

	/* Emit to json. */
	emitter_init(&emitter, emitter_output_json_compact,
	    buffered_write_cb, &prof_log_stop_buf_arg);

	emitter_begin(&emitter);
	prof_log_emit_metadata(&emitter);
	prof_log_emit_threads(tsd, &emitter);
	prof_log_emit_traces(tsd, &emitter);
	prof_log_emit_allocs(tsd, &emitter);
	emitter_end(&emitter);

	buf_writer_flush(&prof_log_stop_buf_arg);
	idalloctm(tsdn, prof_log_stop_buf, NULL, NULL, true, true);

	/* Reset global state. */
	if (log_tables_initialized) {
		ckh_delete(tsd, &log_bt_node_set);
		ckh_delete(tsd, &log_thr_node_set);
	}
	log_tables_initialized = false;
	log_bt_index = 0;
	log_thr_index = 0;
	log_bt_first = NULL;
	log_bt_last = NULL;
	log_thr_first = NULL;
	log_thr_last = NULL;
	log_alloc_first = NULL;
	log_alloc_last = NULL;

	malloc_mutex_lock(tsdn, &log_mtx);
	prof_logging_state = prof_logging_state_stopped;
	malloc_mutex_unlock(tsdn, &log_mtx);

#ifdef JEMALLOC_JET
	if (prof_log_dummy) {
		return false;
	}
#endif
	return close(fd) || arg.ret == -1;
}