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
 int /*<<< orphan*/  JV_KIND_ARRAY ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_invalid () ; 
 int /*<<< orphan*/ * jvp_array_read (int /*<<< orphan*/ ,int) ; 

jv jv_array_get(jv j, int idx) {
  assert(JVP_HAS_KIND(j, JV_KIND_ARRAY));
  jv* slot = jvp_array_read(j, idx);
  jv val;
  if (slot) {
    val = jv_copy(*slot);
  } else {
    val = jv_invalid();
  }
  jv_free(j);
  return val;
}