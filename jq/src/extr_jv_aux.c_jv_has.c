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
 scalar_t__ JV_KIND_NULL ; 
 scalar_t__ JV_KIND_NUMBER ; 
 scalar_t__ JV_KIND_OBJECT ; 
 scalar_t__ JV_KIND_STRING ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_array_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jv_bool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_false () ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_invalid_with_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_kind_name (scalar_t__) ; 
 scalar_t__ jv_number_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_object_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string_fmt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

jv jv_has(jv t, jv k) {
  assert(jv_is_valid(t));
  assert(jv_is_valid(k));
  jv ret;
  if (jv_get_kind(t) == JV_KIND_NULL) {
    jv_free(t);
    jv_free(k);
    ret = jv_false();
  } else if (jv_get_kind(t) == JV_KIND_OBJECT &&
             jv_get_kind(k) == JV_KIND_STRING) {
    jv elem = jv_object_get(t, k);
    ret = jv_bool(jv_is_valid(elem));
    jv_free(elem);
  } else if (jv_get_kind(t) == JV_KIND_ARRAY &&
             jv_get_kind(k) == JV_KIND_NUMBER) {
    jv elem = jv_array_get(t, (int)jv_number_value(k));
    ret = jv_bool(jv_is_valid(elem));
    jv_free(k);
    jv_free(elem);
  } else {
    ret = jv_invalid_with_msg(jv_string_fmt("Cannot check whether %s has a %s key",
                                            jv_kind_name(jv_get_kind(t)),
                                            jv_kind_name(jv_get_kind(k))));
    jv_free(t);
    jv_free(k);
  }
  return ret;
}