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
 int /*<<< orphan*/  BACKTRACK ; 
 int /*<<< orphan*/  BLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENLABEL ; 
 int /*<<< orphan*/  LOADV ; 
 int /*<<< orphan*/  POP ; 
 int /*<<< orphan*/  gen_call (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_cond (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_lambda (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_noop () ; 
 int /*<<< orphan*/  gen_op_simple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_op_unbound (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  gen_try (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_wildvar_binding (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

block gen_label(const char *label, block exp) {
  block cond = gen_call("_equal",
                        BLOCK(gen_lambda(gen_noop()),
                              gen_lambda(gen_op_unbound(LOADV, label))));
  return gen_wildvar_binding(gen_op_simple(GENLABEL), label,
                             BLOCK(gen_op_simple(POP),
                                   // try exp catch if . == $label
                                   //               then empty
                                   //               else error end
                                   //
                                   // Can't use gen_binop(), as that's firmly
                                   // stuck in parser.y as it refers to things
                                   // like EQ.
                                   gen_try(exp,
                                           gen_cond(cond,
                                                    gen_op_simple(BACKTRACK),
                                                    gen_call("error", gen_noop())))));
}