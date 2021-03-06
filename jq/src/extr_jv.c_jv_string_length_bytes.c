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
 int /*<<< orphan*/  JVP_HAS_KIND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JV_KIND_STRING ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int jvp_string_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jvp_string_ptr (int /*<<< orphan*/ ) ; 

int jv_string_length_bytes(jv j) {
  assert(JVP_HAS_KIND(j, JV_KIND_STRING));
  int r = jvp_string_length(jvp_string_ptr(j));
  jv_free(j);
  return r;
}