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
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int jvp_array_length (int /*<<< orphan*/ ) ; 
 scalar_t__ jvp_array_offset (int /*<<< orphan*/ ) ; 
 scalar_t__ jvp_array_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jvp_array_read (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int jvp_array_equal(jv a, jv b) {
  if (jvp_array_length(a) != jvp_array_length(b))
    return 0;
  if (jvp_array_ptr(a) == jvp_array_ptr(b) &&
      jvp_array_offset(a) == jvp_array_offset(b))
    return 1;
  for (int i=0; i<jvp_array_length(a); i++) {
    if (!jv_equal(jv_copy(*jvp_array_read(a, i)),
                  jv_copy(*jvp_array_read(b, i))))
      return 0;
  }
  return 1;
}