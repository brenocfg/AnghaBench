#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jv ;
struct TYPE_3__ {int /*<<< orphan*/  stk_top; int /*<<< orphan*/  stk; } ;
typedef  TYPE_1__ jq_state ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_null () ; 
 int /*<<< orphan*/ * stack_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_pop_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stack_pop_will_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

jv stack_popn(jq_state *jq) {
  jv* sval = stack_block(&jq->stk, jq->stk_top);
  jv val = *sval;
  if (!stack_pop_will_free(&jq->stk, jq->stk_top)) {
    *sval = jv_null();
  }
  jq->stk_top = stack_pop_block(&jq->stk, jq->stk_top, sizeof(jv));
  assert(jv_is_valid(val));
  return val;
}