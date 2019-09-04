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
typedef  void* jv ;
struct TYPE_4__ {scalar_t__ buf_valid_len; char* buf; void* slurped; int /*<<< orphan*/ * parser; } ;
typedef  TYPE_1__ jq_util_input_state ;

/* Variables and functions */
 int jq_util_input_read_more (TYPE_1__*) ; 
 void* jv_array_append (void*,void*) ; 
 int /*<<< orphan*/  jv_copy (void*) ; 
 void* jv_invalid () ; 
 scalar_t__ jv_invalid_has_msg (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_is_valid (void*) ; 
 void* jv_parser_next (int /*<<< orphan*/ *) ; 
 int jv_parser_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jv_parser_set_buf (int /*<<< orphan*/ *,char*,scalar_t__,int) ; 
 void* jv_string (char*) ; 
 void* jv_string_concat (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string_sized (char*,scalar_t__) ; 

jv jq_util_input_next_input(jq_util_input_state *state) {
  int is_last = 0;
  int has_more = 0;
  jv value = jv_invalid(); // need more input
  do {
    if (state->parser == NULL) {
      // Raw input
      is_last = jq_util_input_read_more(state);
      if (state->buf_valid_len == 0)
        continue;
      if (jv_is_valid(state->slurped)) {
        // Slurped raw input
        state->slurped = jv_string_concat(state->slurped, jv_string_sized(state->buf, state->buf_valid_len));
      } else {
        if (!jv_is_valid(value))
          value = jv_string("");
        if (state->buf[state->buf_valid_len-1] == '\n') {
          // whole line
          state->buf[state->buf_valid_len-1] = 0;
          return jv_string_concat(value, jv_string_sized(state->buf, state->buf_valid_len-1));
        }
        value = jv_string_concat(value, jv_string_sized(state->buf, state->buf_valid_len));
        state->buf[0] = '\0';
        state->buf_valid_len = 0;
      }
    } else {
      if (jv_parser_remaining(state->parser) == 0) {
        is_last = jq_util_input_read_more(state);
        if (is_last && state->buf_valid_len == 0)
          value = jv_invalid();
        jv_parser_set_buf(state->parser, state->buf, state->buf_valid_len, !is_last);
      }
      value = jv_parser_next(state->parser);
      if (jv_is_valid(state->slurped)) {
        // When slurping an input that doesn't have a trailing newline,
        // we might have more than one value on the same line, so let's check
        // to see if we have more data to parse.
        has_more = jv_parser_remaining(state->parser);
        if (jv_is_valid(value)) {
          state->slurped = jv_array_append(state->slurped, value);
          value = jv_invalid();
        } else if (jv_invalid_has_msg(jv_copy(value)))
          return value; // Not slurped parsed input
      } else if (jv_is_valid(value) || jv_invalid_has_msg(jv_copy(value))) {
        return value;
      }
    }
  } while (!is_last || has_more);

  if (jv_is_valid(state->slurped)) {
    value = state->slurped;
    state->slurped = jv_invalid();
  }
  return value;
}