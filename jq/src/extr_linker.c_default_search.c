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
 int /*<<< orphan*/  JV_ARRAY (int /*<<< orphan*/ ) ; 
 scalar_t__ JV_KIND_ARRAY ; 
 int /*<<< orphan*/  jq_get_lib_dirs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jv_array_concat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (char*) ; 

__attribute__((used)) static jv default_search(jq_state *jq, jv value) {
  if (!jv_is_valid(value)) {
    // dependent didn't say; prepend . to system search path listj
    jv_free(value);
    return jv_array_concat(JV_ARRAY(jv_string(".")), jq_get_lib_dirs(jq));
  }
  if (jv_get_kind(value) != JV_KIND_ARRAY)
    return JV_ARRAY(value);
  return value;
}