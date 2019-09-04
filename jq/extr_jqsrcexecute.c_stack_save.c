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
typedef  int /*<<< orphan*/  uint16_t ;
struct stack_pos {int /*<<< orphan*/  saved_curr_frame; int /*<<< orphan*/  saved_data_stack; } ;
struct forkpoint {int /*<<< orphan*/ * return_address; int /*<<< orphan*/  subexp_nest; int /*<<< orphan*/  value_at_path; int /*<<< orphan*/  path_len; int /*<<< orphan*/  saved_curr_frame; int /*<<< orphan*/  saved_data_stack; } ;
struct TYPE_3__ {int /*<<< orphan*/  curr_frame; int /*<<< orphan*/  stk_top; int /*<<< orphan*/  subexp_nest; int /*<<< orphan*/  value_at_path; int /*<<< orphan*/  path; int /*<<< orphan*/  fork_top; int /*<<< orphan*/  stk; } ;
typedef  TYPE_1__ jq_state ;

/* Variables and functions */
 scalar_t__ JV_KIND_ARRAY ; 
 int /*<<< orphan*/  jv_array_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 struct forkpoint* stack_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_push_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void stack_save(jq_state *jq, uint16_t* retaddr, struct stack_pos sp){
  jq->fork_top = stack_push_block(&jq->stk, jq->fork_top, sizeof(struct forkpoint));
  struct forkpoint* fork = stack_block(&jq->stk, jq->fork_top);
  fork->saved_data_stack = jq->stk_top;
  fork->saved_curr_frame = jq->curr_frame;
  fork->path_len =
    jv_get_kind(jq->path) == JV_KIND_ARRAY ? jv_array_length(jv_copy(jq->path)) : 0;
  fork->value_at_path = jv_copy(jq->value_at_path);
  fork->subexp_nest = jq->subexp_nest;
  fork->return_address = retaddr;
  jq->stk_top = sp.saved_data_stack;
  jq->curr_frame = sp.saved_curr_frame;
}