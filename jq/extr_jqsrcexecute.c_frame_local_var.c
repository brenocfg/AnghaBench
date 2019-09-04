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
struct jq_state {int /*<<< orphan*/  stk; } ;
struct frame {TYPE_2__* bc; TYPE_1__* entries; } ;
typedef  int /*<<< orphan*/  jv ;
struct TYPE_4__ {int nlocals; int nclosures; } ;
struct TYPE_3__ {int /*<<< orphan*/  localvar; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  frame_get_level (struct jq_state*,int) ; 
 struct frame* stack_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static jv* frame_local_var(struct jq_state* jq, int var, int level) {
  struct frame* fr = stack_block(&jq->stk, frame_get_level(jq, level));
  assert(var >= 0);
  assert(var < fr->bc->nlocals);
  return &fr->entries[fr->bc->nclosures + var].localvar;
}