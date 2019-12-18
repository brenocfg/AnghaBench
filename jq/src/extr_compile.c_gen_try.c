#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  last; int /*<<< orphan*/  first; } ;
typedef  TYPE_1__ block ;

/* Variables and functions */
 TYPE_1__ BLOCK (TYPE_1__,TYPE_1__,...) ; 
 int /*<<< orphan*/  DUP ; 
 int /*<<< orphan*/  FORK_OPT ; 
 int /*<<< orphan*/  JUMP ; 
 int /*<<< orphan*/  POP ; 
 TYPE_1__ gen_op_simple (int /*<<< orphan*/ ) ; 
 TYPE_1__ gen_op_target (int /*<<< orphan*/ ,TYPE_1__) ; 

block gen_try(block exp, block handler) {
  /*
   * Produce something like:
   *  FORK_OPT <address of handler>
   *  <exp>
   *  JUMP <end of handler>
   *  <handler>
   *
   * If this is not an internal try/catch, then catch and re-raise
   * internal errors to prevent them from leaking.
   *
   * The handler will only execute if we backtrack to the FORK_OPT with
   * an error (exception).  If <exp> produces no value then FORK_OPT
   * will backtrack (propagate the `empty`, as it were.  If <exp>
   * produces a value then we'll execute whatever bytecode follows this
   * sequence.
   */
  if (!handler.first && !handler.last)
    // A hack to deal with `.` as the handler; we could use a real NOOP here
    handler = BLOCK(gen_op_simple(DUP), gen_op_simple(POP), handler);
  exp = BLOCK(exp, gen_op_target(JUMP, handler));
  return BLOCK(gen_op_target(FORK_OPT, exp), exp, handler);
}