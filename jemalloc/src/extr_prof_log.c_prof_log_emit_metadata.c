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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  nstime_t ;
typedef  int /*<<< orphan*/  emitter_t ;

/* Variables and functions */
 char* JEMALLOC_VERSION ; 
 int /*<<< orphan*/  NSTIME_ZERO_INITIALIZER ; 
 int /*<<< orphan*/  emitter_json_kv (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  emitter_json_object_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_json_object_kv_begin (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  emitter_type_int ; 
 int /*<<< orphan*/  emitter_type_string ; 
 int /*<<< orphan*/  emitter_type_uint64 ; 
 int lg_prof_sample ; 
 int /*<<< orphan*/  log_start_timestamp ; 
 int nstime_ns (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nstime_update (int /*<<< orphan*/ *) ; 
 int prof_getpid () ; 

__attribute__((used)) static void
prof_log_emit_metadata(emitter_t *emitter) {
	emitter_json_object_kv_begin(emitter, "info");

	nstime_t now = NSTIME_ZERO_INITIALIZER;

	nstime_update(&now);
	uint64_t ns = nstime_ns(&now) - nstime_ns(&log_start_timestamp);
	emitter_json_kv(emitter, "duration", emitter_type_uint64, &ns);

	char *vers = JEMALLOC_VERSION;
	emitter_json_kv(emitter, "version",
	    emitter_type_string, &vers);

	emitter_json_kv(emitter, "lg_sample_rate",
	    emitter_type_int, &lg_prof_sample);

	int pid = prof_getpid();
	emitter_json_kv(emitter, "pid", emitter_type_int, &pid);

	emitter_json_object_end(emitter);
}