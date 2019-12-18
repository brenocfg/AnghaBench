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
struct jq_state {int /*<<< orphan*/  stk; int /*<<< orphan*/  curr_frame; } ;
struct frame {int /*<<< orphan*/  env; } ;
typedef  int /*<<< orphan*/  stack_ptr ;

/* Variables and functions */
 struct frame* stack_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static stack_ptr frame_get_level(struct jq_state* jq, int level) {
  stack_ptr fr = jq->curr_frame;
  for (int i=0; i<level; i++) {
    struct frame* fp = stack_block(&jq->stk, fr);
    fr = fp->env;
  }
  return fr;
}