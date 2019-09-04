#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct jq_state {int /*<<< orphan*/  stk; } ;
struct frame {TYPE_2__* entries; TYPE_1__* bc; } ;
struct closure {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  stack_ptr ;
struct TYPE_4__ {struct closure closure; } ;
struct TYPE_3__ {int nsubfunctions; int nclosures; int /*<<< orphan*/ * subfunctions; } ;

/* Variables and functions */
 int ARG_NEWCLOSURE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  frame_get_level (struct jq_state*,int) ; 
 struct frame* stack_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct closure make_closure(struct jq_state* jq, uint16_t* pc) {
  uint16_t level = *pc++;
  uint16_t idx = *pc++;
  stack_ptr fridx = frame_get_level(jq, level);
  struct frame* fr = stack_block(&jq->stk, fridx);
  if (idx & ARG_NEWCLOSURE) {
    // A new closure closing the frame identified by level, and with
    // the bytecode body of the idx'th subfunction of that frame
    int subfn_idx = idx & ~ARG_NEWCLOSURE;
    assert(subfn_idx < fr->bc->nsubfunctions);
    struct closure cl = {fr->bc->subfunctions[subfn_idx],
                         fridx};
    return cl;
  } else {
    // A reference to a closure from the frame identified by level; copy
    // it as-is
    int closure = idx;
    assert(closure >= 0);
    assert(closure < fr->bc->nclosures);
    return fr->entries[closure].closure;
  }
}