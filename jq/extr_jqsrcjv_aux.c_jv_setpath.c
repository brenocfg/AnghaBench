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
 int /*<<< orphan*/  jv_array_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jv_array_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_array_slice (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_invalid_with_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (char*) ; 

jv jv_setpath(jv root, jv path, jv value) {
  if (jv_get_kind(path) != JV_KIND_ARRAY) {
    jv_free(value);
    jv_free(root);
    jv_free(path);
    return jv_invalid_with_msg(jv_string("Path must be specified as an array"));
  }
  if (!jv_is_valid(root)){
    jv_free(value);
    jv_free(path);
    return root;
  }
  if (jv_array_length(jv_copy(path)) == 0) {
    jv_free(path);
    jv_free(root);
    return value;
  }
  jv pathcurr = jv_array_get(jv_copy(path), 0);
  jv pathrest = jv_array_slice(path, 1, jv_array_length(jv_copy(path)));
  return jv_set(root, pathcurr,
                jv_setpath(jv_get(jv_copy(root), jv_copy(pathcurr)), pathrest, value));
}