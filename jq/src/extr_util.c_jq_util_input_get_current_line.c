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
struct TYPE_2__ {int /*<<< orphan*/  current_line; } ;
typedef  TYPE_1__ jq_util_input_state ;
typedef  int /*<<< orphan*/  jq_state ;
typedef  scalar_t__ jq_input_cb ;

/* Variables and functions */
 int /*<<< orphan*/  jq_get_input_cb (int /*<<< orphan*/ *,scalar_t__*,void**) ; 
 scalar_t__ jq_util_input_next_input_cb ; 
 int /*<<< orphan*/  jv_invalid_with_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (char*) ; 

jv jq_util_input_get_current_line(jq_state* jq) {
  jq_input_cb cb=NULL;
  void *cb_data=NULL;
  jq_get_input_cb(jq, &cb, &cb_data);
  if (cb != jq_util_input_next_input_cb)
    return jv_invalid_with_msg(jv_string("Unknown input line number"));
  jq_util_input_state *s = (jq_util_input_state *)cb_data;
  jv v = jv_number(s->current_line);
  return v;
}