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
typedef  int /*<<< orphan*/  jv ;
typedef  int /*<<< orphan*/  jq_state ;

/* Variables and functions */
 int ASCII_OUTPUT ; 
 int EXIT_STATUS_EXACT ; 
 int JQ_ERROR_UNKNOWN ; 
 int JQ_OK ; 
 int JQ_OK_NO_OUTPUT ; 
 int JQ_OK_NULL_KIND ; 
 scalar_t__ JV_KIND_FALSE ; 
 scalar_t__ JV_KIND_NULL ; 
 scalar_t__ JV_KIND_NUMBER ; 
 scalar_t__ JV_KIND_STRING ; 
 int /*<<< orphan*/  JV_PRINT_ASCII ; 
 int JV_PRINT_ISATTY ; 
 int RAW_NO_LF ; 
 int RAW_OUTPUT ; 
 int SEQ ; 
 int UNBUFFERED_OUTPUT ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  fwrite (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jq_get_error_message (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jq_get_exit_code (int /*<<< orphan*/ *) ; 
 scalar_t__ jq_halted (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jq_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jq_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jq_util_input_get_position (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_dump (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jv_dump_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_dumpf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_invalid_get_msg (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_invalid_has_msg (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_is_valid (int /*<<< orphan*/ ) ; 
 int jv_number_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string_length_bytes (int /*<<< orphan*/ ) ; 
 char* jv_string_value (int /*<<< orphan*/ ) ; 
 int options ; 
 int /*<<< orphan*/  priv_fwrite (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int process(jq_state *jq, jv value, int flags, int dumpopts) {
  int ret = JQ_OK_NO_OUTPUT; // No valid results && -e -> exit(4)
  jq_start(jq, value, flags);
  jv result;
  while (jv_is_valid(result = jq_next(jq))) {
    if ((options & RAW_OUTPUT) && jv_get_kind(result) == JV_KIND_STRING) {
      if (options & ASCII_OUTPUT) {
        jv_dumpf(jv_copy(result), stdout, JV_PRINT_ASCII);
      } else {
        fwrite(jv_string_value(result), 1, jv_string_length_bytes(jv_copy(result)), stdout);
      }
      ret = JQ_OK;
      jv_free(result);
    } else {
      if (jv_get_kind(result) == JV_KIND_FALSE || jv_get_kind(result) == JV_KIND_NULL)
        ret = JQ_OK_NULL_KIND;
      else
        ret = JQ_OK;
      if (options & SEQ)
        priv_fwrite("\036", 1, stdout, dumpopts & JV_PRINT_ISATTY);
      jv_dump(result, dumpopts);
    }
    if (!(options & RAW_NO_LF))
      priv_fwrite("\n", 1, stdout, dumpopts & JV_PRINT_ISATTY);
    if (options & UNBUFFERED_OUTPUT)
      fflush(stdout);
  }
  if (jq_halted(jq)) {
    // jq program invoked `halt` or `halt_error`
    options |= EXIT_STATUS_EXACT;
    jv exit_code = jq_get_exit_code(jq);
    if (!jv_is_valid(exit_code))
      ret = JQ_OK;
    else if (jv_get_kind(exit_code) == JV_KIND_NUMBER)
      ret = jv_number_value(exit_code);
    else
      ret = JQ_ERROR_UNKNOWN;
    jv_free(exit_code);
    jv error_message = jq_get_error_message(jq);
    if (jv_get_kind(error_message) == JV_KIND_STRING) {
      fprintf(stderr, "jq: error: %s", jv_string_value(error_message));
    } else if (jv_get_kind(error_message) == JV_KIND_NULL) {
      // Halt with no output
    } else if (jv_is_valid(error_message)) {
      error_message = jv_dump_string(jv_copy(error_message), 0);
      fprintf(stderr, "jq: error: %s\n", jv_string_value(error_message));
    } // else no message on stderr; use --debug-trace to see a message
    fflush(stderr);
    jv_free(error_message);
  } else if (jv_invalid_has_msg(jv_copy(result))) {
    // Uncaught jq exception
    jv msg = jv_invalid_get_msg(jv_copy(result));
    jv input_pos = jq_util_input_get_position(jq);
    if (jv_get_kind(msg) == JV_KIND_STRING) {
      fprintf(stderr, "jq: error (at %s): %s\n",
              jv_string_value(input_pos), jv_string_value(msg));
    } else {
      msg = jv_dump_string(msg, 0);
      fprintf(stderr, "jq: error (at %s) (not a string): %s\n",
              jv_string_value(input_pos), jv_string_value(msg));
    }
    ret = JQ_ERROR_UNKNOWN;
    jv_free(input_pos);
    jv_free(msg);
  }
  jv_free(result);
  return ret;
}