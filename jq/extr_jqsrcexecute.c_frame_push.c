#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
union frame_entry {int /*<<< orphan*/  localvar; int /*<<< orphan*/  closure; } ;
typedef  int /*<<< orphan*/  uint16_t ;
struct jq_state {int /*<<< orphan*/  curr_frame; int /*<<< orphan*/  stk; } ;
struct frame {union frame_entry* entries; TYPE_1__* bc; int /*<<< orphan*/  env; } ;
struct closure {TYPE_1__* bc; int /*<<< orphan*/  env; } ;
typedef  int /*<<< orphan*/  stack_ptr ;
struct TYPE_2__ {int nclosures; int nlocals; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  frame_size (TYPE_1__*) ; 
 int /*<<< orphan*/  jv_invalid () ; 
 int /*<<< orphan*/  make_closure (struct jq_state*,int /*<<< orphan*/ *) ; 
 struct frame* stack_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_push_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct frame* frame_push(struct jq_state* jq, struct closure callee,
                                uint16_t* argdef, int nargs) {
  stack_ptr new_frame_idx = stack_push_block(&jq->stk, jq->curr_frame, frame_size(callee.bc));
  struct frame* new_frame = stack_block(&jq->stk, new_frame_idx);
  new_frame->bc = callee.bc;
  new_frame->env = callee.env;
  assert(nargs == new_frame->bc->nclosures);
  union frame_entry* entries = new_frame->entries;
  for (int i=0; i<nargs; i++) {
    entries->closure = make_closure(jq, argdef + i * 2);
    entries++;
  }
  for (int i=0; i<callee.bc->nlocals; i++) {
    entries->localvar = jv_invalid();
    entries++;
  }
  jq->curr_frame = new_frame_idx;
  return new_frame;
}