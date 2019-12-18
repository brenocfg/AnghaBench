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
 int /*<<< orphan*/  BLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  INDEX ; 
 int /*<<< orphan*/  gen_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_call (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_cond (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_lambda (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_noop () ; 
 int /*<<< orphan*/  gen_op_simple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_subexp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (char*) ; 

block gen_try_handler(block handler) {
  // Quite a pain just to hide jq's internal errors.
  return gen_cond(// `if type=="object" and .__jq
                  gen_and(gen_call("_equal",
                                   BLOCK(gen_lambda(gen_const(jv_string("object"))),
                                         gen_lambda(gen_noop()))),
                          BLOCK(gen_subexp(gen_const(jv_string("__jq"))),
                                gen_noop(),
                                gen_op_simple(INDEX))),
                  // `then error`
                  gen_call("error", gen_noop()),
                  // `else HANDLER end`
                  handler);
}