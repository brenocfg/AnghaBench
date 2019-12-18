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
typedef  scalar_t__ jv_kind ;
typedef  int /*<<< orphan*/  jv ;
typedef  int /*<<< orphan*/  jq_state ;

/* Variables and functions */
 scalar_t__ JV_KIND_NUMBER ; 
 scalar_t__ JV_KIND_OBJECT ; 
 scalar_t__ JV_KIND_STRING ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_null () ; 
 int /*<<< orphan*/  jv_number (int) ; 
 int jv_number_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_object_merge_recursive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string_append_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 size_t jv_string_length_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_error2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static jv f_multiply(jq_state *jq, jv input, jv a, jv b) {
  jv_kind ak = jv_get_kind(a);
  jv_kind bk = jv_get_kind(b);
  jv_free(input);
  if (ak == JV_KIND_NUMBER && bk == JV_KIND_NUMBER) {
    jv r = jv_number(jv_number_value(a) * jv_number_value(b));
    jv_free(a);
    jv_free(b);
    return r;
  } else if ((ak == JV_KIND_STRING && bk == JV_KIND_NUMBER) ||
             (ak == JV_KIND_NUMBER && bk == JV_KIND_STRING)) {
    jv str = a;
    jv num = b;
    if (ak == JV_KIND_NUMBER) {
      str = b;
      num = a;
    }
    int n;
    size_t alen = jv_string_length_bytes(jv_copy(str));
    jv res = str;

    for (n = jv_number_value(num) - 1; n > 0; n--)
      res = jv_string_append_buf(res, jv_string_value(str), alen);

    jv_free(num);
    if (n < 0) {
      jv_free(str);
      return jv_null();
    }
    return res;
  } else if (ak == JV_KIND_OBJECT && bk == JV_KIND_OBJECT) {
    return jv_object_merge_recursive(a, b);
  } else {
    return type_error2(a, b, "cannot be multiplied");
  }
}