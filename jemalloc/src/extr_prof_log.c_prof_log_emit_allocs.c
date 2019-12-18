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
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  usize; int /*<<< orphan*/  free_time_ns; int /*<<< orphan*/  alloc_time_ns; int /*<<< orphan*/  free_bt_ind; int /*<<< orphan*/  alloc_bt_ind; int /*<<< orphan*/  free_thr_ind; int /*<<< orphan*/  alloc_thr_ind; } ;
typedef  TYPE_1__ prof_alloc_node_t ;
typedef  int /*<<< orphan*/  emitter_t ;

/* Variables and functions */
 int /*<<< orphan*/  emitter_json_array_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_json_array_kv_begin (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  emitter_json_kv (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_json_object_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_json_object_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_type_size ; 
 int /*<<< orphan*/  emitter_type_uint64 ; 
 int /*<<< orphan*/  idalloctm (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 TYPE_1__* log_alloc_first ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
prof_log_emit_allocs(tsd_t *tsd, emitter_t *emitter) {
	emitter_json_array_kv_begin(emitter, "allocations");
	prof_alloc_node_t *alloc_node = log_alloc_first;
	prof_alloc_node_t *alloc_old_node;
	while (alloc_node != NULL) {
		emitter_json_object_begin(emitter);

		emitter_json_kv(emitter, "alloc_thread", emitter_type_size,
		    &alloc_node->alloc_thr_ind);

		emitter_json_kv(emitter, "free_thread", emitter_type_size,
		    &alloc_node->free_thr_ind);

		emitter_json_kv(emitter, "alloc_trace", emitter_type_size,
		    &alloc_node->alloc_bt_ind);

		emitter_json_kv(emitter, "free_trace", emitter_type_size,
		    &alloc_node->free_bt_ind);

		emitter_json_kv(emitter, "alloc_timestamp",
		    emitter_type_uint64, &alloc_node->alloc_time_ns);

		emitter_json_kv(emitter, "free_timestamp", emitter_type_uint64,
		    &alloc_node->free_time_ns);

		emitter_json_kv(emitter, "usize", emitter_type_uint64,
		    &alloc_node->usize);

		emitter_json_object_end(emitter);

		alloc_old_node = alloc_node;
		alloc_node = alloc_node->next;
		idalloctm(tsd_tsdn(tsd), alloc_old_node, NULL, NULL, true,
		    true);
	}
	emitter_json_array_end(emitter);
}