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
 scalar_t__ JV_KIND_NUMBER ; 
 scalar_t__ JV_KIND_STRING ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_parse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_error (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static jv f_tonumber(jq_state *jq, jv input) {
  if (jv_get_kind(input) == JV_KIND_NUMBER) {
    return input;
  }
  if (jv_get_kind(input) == JV_KIND_STRING) {
    jv parsed = jv_parse(jv_string_value(input));
    if (!jv_is_valid(parsed) || jv_get_kind(parsed) == JV_KIND_NUMBER) {
      jv_free(input);
      return parsed;
    }
  }
  return type_error(input, "cannot be parsed as a number");
}