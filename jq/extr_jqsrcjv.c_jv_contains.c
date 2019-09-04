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
 scalar_t__ JV_KIND_ARRAY ; 
 scalar_t__ JV_KIND_OBJECT ; 
 scalar_t__ JV_KIND_STRING ; 
 scalar_t__ _jq_memmem (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int jv_array_contains (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int jv_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int jv_object_contains (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int jv_string_length_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string_value (int /*<<< orphan*/ ) ; 

int jv_contains(jv a, jv b) {
  int r = 1;
  if (jv_get_kind(a) != jv_get_kind(b)) {
    r = 0;
  } else if (jv_get_kind(a) == JV_KIND_OBJECT) {
    r = jv_object_contains(jv_copy(a), jv_copy(b));
  } else if (jv_get_kind(a) == JV_KIND_ARRAY) {
    r = jv_array_contains(jv_copy(a), jv_copy(b));
  } else if (jv_get_kind(a) == JV_KIND_STRING) {
    int b_len = jv_string_length_bytes(jv_copy(b));
    if (b_len != 0) {
      r = _jq_memmem(jv_string_value(a), jv_string_length_bytes(jv_copy(a)),
                     jv_string_value(b), b_len) != 0;
    } else {
      r = 1;
    }
  } else {
    r = jv_equal(jv_copy(a), jv_copy(b));
  }
  jv_free(a);
  jv_free(b);
  return r;
}