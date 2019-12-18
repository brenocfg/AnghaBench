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
typedef  int /*<<< orphan*/  block ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSURE_PARAM_REGULAR ; 
 int /*<<< orphan*/  gen_op_unbound (int /*<<< orphan*/ ,char const*) ; 

block gen_param_regular(const char* name) {
  return gen_op_unbound(CLOSURE_PARAM_REGULAR, name);
}