#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jv ;
struct TYPE_2__ {scalar_t__ current_line; int /*<<< orphan*/  current_filename; } ;
typedef  TYPE_1__ jq_util_input_state ;
typedef  int /*<<< orphan*/  jq_state ;
typedef  scalar_t__ jq_input_cb ;

/* Variables and functions */
 scalar_t__ JV_KIND_STRING ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  jq_get_input_cb (int /*<<< orphan*/ *,scalar_t__*,void**) ; 
 scalar_t__ jq_util_input_next_input_cb ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_invalid_with_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (char*) ; 
 int /*<<< orphan*/  jv_string_fmt (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  jv_string_value (int /*<<< orphan*/ ) ; 

jv jq_util_input_get_position(jq_state *jq) {
  jq_input_cb cb = NULL;
  void *cb_data = NULL;
  jq_get_input_cb(jq, &cb, &cb_data);
  assert(cb == jq_util_input_next_input_cb);
  if (cb != jq_util_input_next_input_cb)
    return jv_invalid_with_msg(jv_string("Invalid jq_util_input API usage"));
  jq_util_input_state *s = (jq_util_input_state *)cb_data;

  // We can't assert that current_filename is a string because if
  // the error was a JSON parser error then we may not have set
  // current_filename yet.
  if (jv_get_kind(s->current_filename) != JV_KIND_STRING)
    return jv_string("<unknown>");

  jv v = jv_string_fmt("%s:%lu", jv_string_value(s->current_filename), (unsigned long)s->current_line);
  return v;
}