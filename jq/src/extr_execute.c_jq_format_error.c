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

/* Variables and functions */
 scalar_t__ JV_KIND_INVALID ; 
 scalar_t__ JV_KIND_NULL ; 
 scalar_t__ JV_KIND_STRING ; 
 int /*<<< orphan*/  JV_PRINT_INVALID ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_dump_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_invalid_get_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_invalid_has_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_null () ; 
 int /*<<< orphan*/  jv_string_fmt (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

jv jq_format_error(jv msg) {
  if (jv_get_kind(msg) == JV_KIND_NULL ||
      (jv_get_kind(msg) == JV_KIND_INVALID && !jv_invalid_has_msg(jv_copy(msg)))) {
    jv_free(msg);
    fprintf(stderr, "jq: error: out of memory\n");
    return jv_null();
  }

  if (jv_get_kind(msg) == JV_KIND_STRING)
    return msg;                         // expected to already be formatted

  if (jv_get_kind(msg) == JV_KIND_INVALID)
    msg = jv_invalid_get_msg(msg);

  if (jv_get_kind(msg) == JV_KIND_NULL)
    return jq_format_error(msg);        // ENOMEM

  // Invalid with msg; prefix with "jq: error: "

  if (jv_get_kind(msg) != JV_KIND_INVALID) {
    if (jv_get_kind(msg) == JV_KIND_STRING)
      return jv_string_fmt("jq: error: %s", jv_string_value(msg));

    msg = jv_dump_string(msg, JV_PRINT_INVALID);
    if (jv_get_kind(msg) == JV_KIND_STRING)
      return jv_string_fmt("jq: error: %s", jv_string_value(msg));
    return jq_format_error(jv_null());  // ENOMEM
  }

  // An invalid inside an invalid!
  return jq_format_error(jv_invalid_get_msg(msg));
}