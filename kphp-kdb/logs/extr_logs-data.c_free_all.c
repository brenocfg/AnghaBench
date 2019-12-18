#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  event ;
struct TYPE_3__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int FN ; 
 int MAX_EV ; 
 int MAX_EVENT_MEM ; 
 size_t MAX_HISTORY ; 
 int MAX_TYPE ; 
 int /*<<< orphan*/  ans ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * color_int ; 
 int /*<<< orphan*/ * color_ll ; 
 int /*<<< orphan*/  dl_free (int /*<<< orphan*/ ,int) ; 
 scalar_t__ dl_get_memory_used () ; 
 int /*<<< orphan*/  dl_strfree (scalar_t__) ; 
 int /*<<< orphan*/  dump_expr ; 
 scalar_t__ dump_mode ; 
 int /*<<< orphan*/ * dump_query ; 
 int /*<<< orphan*/  eq ; 
 scalar_t__ eq_n ; 
 int /*<<< orphan*/  event_free () ; 
 int /*<<< orphan*/  events_mem ; 
 scalar_t__ events_memory ; 
 int /*<<< orphan*/  expression_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 size_t history_l ; 
 scalar_t__* history_q ; 
 size_t history_r ; 
 int /*<<< orphan*/  log_crc32 ; 
 int /*<<< orphan*/  log_position ; 
 int /*<<< orphan*/  log_timestamp ; 
 int /*<<< orphan*/  map_int_int_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_ll_int_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_type_id ; 
 int /*<<< orphan*/ * q_st_int ; 
 int /*<<< orphan*/ * q_st_ll ; 
 scalar_t__* std_t ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ test_mode ; 
 int /*<<< orphan*/  time_table_log_crc32 ; 
 int /*<<< orphan*/  time_table_log_position ; 
 int /*<<< orphan*/  time_table_log_timestamp ; 
 int /*<<< orphan*/  type_free (TYPE_1__*) ; 
 TYPE_1__* types ; 
 int /*<<< orphan*/  vector_free (int /*<<< orphan*/ ) ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  write_only ; 

void free_all (void) {
  if (verbosity > 0 || test_mode) {
    vector_free (log_position);
    vector_free (log_timestamp);
    vector_free (log_crc32);

    vector_free (time_table_log_position);
    vector_free (time_table_log_timestamp);
    vector_free (time_table_log_crc32);

    while (history_l != history_r) {
      dl_strfree (history_q[history_l]);
      history_q[history_l++] = 0;
      if (history_l > MAX_HISTORY) {
        history_l = 0;
      }
    }

    while (eq_n) {
      event_free();
    }
    assert (events_memory == 0);

    if (!write_only) {
      dl_free (events_mem, MAX_EVENT_MEM);
      dl_free (eq, sizeof (event *) * MAX_EV);
      dl_free (ans, sizeof (int) * MAX_EV);
    }

    int i;
    for (i = 0; i < FN; i += 1 + std_t[i]) {
      if (std_t[i]) {
        map_ll_int_free (&color_ll[i]);
        map_ll_int_free (&q_st_ll[i]);
      } else {
        map_int_int_free (&color_int[i]);
        map_int_int_free (&q_st_int[i]);
      }
    }

    for (i = 0; i < MAX_TYPE; i++) {
      if (types[i].name != NULL) {
        type_free (&types[i]);
      }
    }

    map_ll_int_free (&map_type_id);

    if (dump_mode && dump_query != NULL) {
      expression_free (&dump_expr);
    }

    fprintf (stderr, "Memory left: %lld\n", dl_get_memory_used());
//    while (1) {}
    assert (dl_get_memory_used() == 0);
  }
}