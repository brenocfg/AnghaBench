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
 scalar_t__ JV_KIND_TRUE ; 
 int /*<<< orphan*/  f_startswith (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int jv_string_length_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string_sized (scalar_t__,int) ; 
 scalar_t__ jv_string_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static jv f_ltrimstr(jq_state *jq, jv input, jv left) {
  if (jv_get_kind(f_startswith(jq, jv_copy(input), jv_copy(left))) != JV_KIND_TRUE) {
    jv_free(left);
    return input;
  }
  /*
   * FIXME It'd be better to share the suffix with the original input --
   * that we could do, we just can't share prefixes.
   */
  int prefixlen = jv_string_length_bytes(left);
  jv res = jv_string_sized(jv_string_value(input) + prefixlen,
                           jv_string_length_bytes(jv_copy(input)) - prefixlen);
  jv_free(input);
  return res;
}