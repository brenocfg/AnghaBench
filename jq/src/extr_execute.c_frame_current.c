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
struct jq_state {int /*<<< orphan*/  stk; scalar_t__ curr_frame; } ;
struct frame {scalar_t__ retaddr; struct bytecode* bc; } ;
struct bytecode {scalar_t__ code; scalar_t__ codelen; } ;
typedef  scalar_t__ stack_ptr ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct frame* stack_block (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__* stack_block_next (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static struct frame* frame_current(struct jq_state* jq) {
  struct frame* fp = stack_block(&jq->stk, jq->curr_frame);

  stack_ptr next = *stack_block_next(&jq->stk, jq->curr_frame);
  if (next) {
    struct frame* fpnext = stack_block(&jq->stk, next);
    struct bytecode* bc = fpnext->bc;
    assert(fp->retaddr >= bc->code && fp->retaddr < bc->code + bc->codelen);
  } else {
    assert(fp->retaddr == 0);
  }
  return fp;
}