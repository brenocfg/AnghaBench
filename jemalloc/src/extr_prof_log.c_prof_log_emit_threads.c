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
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_4__ {char* thr_uid; char* name; struct TYPE_4__* next; } ;
typedef  TYPE_1__ prof_thr_node_t ;
typedef  int /*<<< orphan*/  emitter_t ;

/* Variables and functions */
 int /*<<< orphan*/  emitter_json_array_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_json_array_kv_begin (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  emitter_json_kv (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  emitter_json_object_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_json_object_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_type_string ; 
 int /*<<< orphan*/  emitter_type_uint64 ; 
 int /*<<< orphan*/  idalloctm (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 TYPE_1__* log_thr_first ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
prof_log_emit_threads(tsd_t *tsd, emitter_t *emitter) {
	emitter_json_array_kv_begin(emitter, "threads");
	prof_thr_node_t *thr_node = log_thr_first;
	prof_thr_node_t *thr_old_node;
	while (thr_node != NULL) {
		emitter_json_object_begin(emitter);

		emitter_json_kv(emitter, "thr_uid", emitter_type_uint64,
		    &thr_node->thr_uid);

		char *thr_name = thr_node->name;

		emitter_json_kv(emitter, "thr_name", emitter_type_string,
		    &thr_name);

		emitter_json_object_end(emitter);
		thr_old_node = thr_node;
		thr_node = thr_node->next;
		idalloctm(tsd_tsdn(tsd), thr_old_node, NULL, NULL, true, true);
	}
	emitter_json_array_end(emitter);
}