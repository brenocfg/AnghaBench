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
 scalar_t__ JV_KIND_ARRAY ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (char*) ; 
 int /*<<< orphan*/  jv_string_implode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ret_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static jv f_string_implode(jq_state *jq, jv a) {
  if (jv_get_kind(a) != JV_KIND_ARRAY) {
    return ret_error(a, jv_string("implode input must be an array"));
  }
  return jv_string_implode(a);
}