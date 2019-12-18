#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  constant; } ;
struct TYPE_14__ {scalar_t__ op; TYPE_2__ imm; struct TYPE_14__* next; } ;
typedef  TYPE_3__ inst ;
struct TYPE_15__ {TYPE_1__* first; } ;
typedef  TYPE_4__ block ;
struct TYPE_12__ {scalar_t__ op; TYPE_3__* next; } ;

/* Variables and functions */
 TYPE_4__ BLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__,TYPE_4__) ; 
 scalar_t__ DUP ; 
 scalar_t__ INDEX ; 
 scalar_t__ LOADK ; 
 scalar_t__ PUSHK_UNDER ; 
 scalar_t__ SUBEXP_BEGIN ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ block_is_noop (TYPE_4__) ; 
 int /*<<< orphan*/  gen_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_op_simple (scalar_t__) ; 
 int /*<<< orphan*/  gen_subexp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_number (int) ; 
 scalar_t__ jv_number_value (int /*<<< orphan*/ ) ; 

block gen_array_matcher(block left, block curr) {
  int index;
  if (block_is_noop(left))
    index = 0;
  else {
    // `left` was returned by this function, so the third inst is the
    // constant containing the previously used index
    assert(left.first->op == DUP);
    assert(left.first->next != NULL);
    inst *i = NULL;
    if (left.first->next->op == PUSHK_UNDER) {
      i = left.first->next;
    } else {
      assert(left.first->next->op == SUBEXP_BEGIN);
      assert(left.first->next->next->op == LOADK);
      i = left.first->next->next;
    }
    index = 1 + (int) jv_number_value(i->imm.constant);
  }

  // `left` goes at the end so that the const index is in a predictable place
  return BLOCK(gen_op_simple(DUP), gen_subexp(gen_const(jv_number(index))),
               gen_op_simple(INDEX), curr, left);
}