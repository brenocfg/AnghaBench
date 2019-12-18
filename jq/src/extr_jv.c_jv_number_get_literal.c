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
 int /*<<< orphan*/  JVP_FLAGS_NUMBER_LITERAL ; 
 scalar_t__ JVP_HAS_FLAGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JVP_HAS_KIND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JV_KIND_NUMBER ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char const* jvp_literal_number_literal (int /*<<< orphan*/ ) ; 

const char* jv_number_get_literal(jv n) {
  assert(JVP_HAS_KIND(n, JV_KIND_NUMBER));

  if (JVP_HAS_FLAGS(n, JVP_FLAGS_NUMBER_LITERAL)) {
    return jvp_literal_number_literal(n);
  } else {
    return NULL;
  }
}