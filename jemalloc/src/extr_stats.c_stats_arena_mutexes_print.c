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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t mutex_prof_arena_ind_t ;
typedef  int /*<<< orphan*/  emitter_t ;
typedef  int /*<<< orphan*/  emitter_row_t ;
typedef  int /*<<< orphan*/  emitter_col_t ;

/* Variables and functions */
 char** arena_mutex_names ; 
 int /*<<< orphan*/  emitter_json_object_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_json_object_kv_begin (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  emitter_row_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_table_row (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t mutex_prof_num_arena_mutexes ; 
 int mutex_prof_num_uint32_t_counters ; 
 int mutex_prof_num_uint64_t_counters ; 
 int /*<<< orphan*/  mutex_stats_emit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_stats_init_cols (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_stats_read_arena (unsigned int,size_t,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
stats_arena_mutexes_print(emitter_t *emitter, unsigned arena_ind, uint64_t uptime) {
	emitter_row_t row;
	emitter_col_t col_name;
	emitter_col_t col64[mutex_prof_num_uint64_t_counters];
	emitter_col_t col32[mutex_prof_num_uint32_t_counters];

	emitter_row_init(&row);
	mutex_stats_init_cols(&row, "", &col_name, col64, col32);

	emitter_json_object_kv_begin(emitter, "mutexes");
	emitter_table_row(emitter, &row);

	for (mutex_prof_arena_ind_t i = 0; i < mutex_prof_num_arena_mutexes;
	    i++) {
		const char *name = arena_mutex_names[i];
		emitter_json_object_kv_begin(emitter, name);
		mutex_stats_read_arena(arena_ind, i, name, &col_name, col64,
		    col32, uptime);
		mutex_stats_emit(emitter, &row, col64, col32);
		emitter_json_object_end(emitter); /* Close the mutex dict. */
	}
	emitter_json_object_end(emitter); /* End "mutexes". */
}