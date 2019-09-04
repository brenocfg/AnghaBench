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
 scalar_t__ JV_KIND_INVALID ; 
 scalar_t__ JV_KIND_OBJECT ; 
 scalar_t__ JV_KIND_STRING ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jvp_array_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jvp_invalid_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jvp_object_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jvp_string_free (int /*<<< orphan*/ ) ; 

void jv_free(jv j) {
  if (jv_get_kind(j) == JV_KIND_ARRAY) {
    jvp_array_free(j);
  } else if (jv_get_kind(j) == JV_KIND_STRING) {
    jvp_string_free(j);
  } else if (jv_get_kind(j) == JV_KIND_OBJECT) {
    jvp_object_free(j);
  } else if (jv_get_kind(j) == JV_KIND_INVALID) {
    jvp_invalid_free(j);
  }
}