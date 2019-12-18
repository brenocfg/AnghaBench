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
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jvp_string_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jvp_string_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jvp_string_ptr (int /*<<< orphan*/ ) ; 

jv jv_string_concat(jv a, jv b) {
  a = jvp_string_append(a, jv_string_value(b),
                        jvp_string_length(jvp_string_ptr(b)));
  jv_free(b);
  return a;
}