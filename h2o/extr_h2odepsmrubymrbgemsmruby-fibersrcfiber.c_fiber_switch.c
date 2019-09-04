#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct mrb_context {int status; TYPE_2__* ci; int /*<<< orphan*/  vmexec; int /*<<< orphan*/ * stack; TYPE_1__* cibase; struct mrb_context* prev; } ;
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_16__ {struct mrb_context* c; struct mrb_context* root_c; } ;
typedef  TYPE_3__ mrb_state ;
typedef  int mrb_int ;
typedef  scalar_t__ mrb_bool ;
typedef  enum mrb_fiber_state { ____Placeholder_mrb_fiber_state } mrb_fiber_state ;
struct TYPE_15__ {int /*<<< orphan*/  pc; int /*<<< orphan*/  proc; } ;
struct TYPE_14__ {int argc; } ;
struct TYPE_13__ {int /*<<< orphan*/ * stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_FIBER_ERROR ; 
 int /*<<< orphan*/  MARK_CONTEXT_MODIFY (struct mrb_context*) ; 
 int MRB_FIBER_CREATED ; 
 int MRB_FIBER_RESUMED ; 
 int MRB_FIBER_RUNNING ; 
 int MRB_FIBER_TERMINATED ; 
 int MRB_FIBER_TRANSFERRED ; 
 TYPE_12__* MRB_PROC_ENV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 struct mrb_context* fiber_check (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fiber_check_cfunc (TYPE_3__*,struct mrb_context*) ; 
 int /*<<< orphan*/  fiber_result (TYPE_3__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  fiber_switch_context (TYPE_3__*,struct mrb_context*) ; 
 int /*<<< orphan*/  mrb_raise (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_stack_extend (TYPE_3__*,int) ; 
 int /*<<< orphan*/  mrb_vm_exec (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
fiber_switch(mrb_state *mrb, mrb_value self, mrb_int len, const mrb_value *a, mrb_bool resume, mrb_bool vmexec)
{
  struct mrb_context *c = fiber_check(mrb, self);
  struct mrb_context *old_c = mrb->c;
  enum mrb_fiber_state status;
  mrb_value value;

  fiber_check_cfunc(mrb, c);
  status = c->status;
  if (resume && status == MRB_FIBER_TRANSFERRED) {
    mrb_raise(mrb, E_FIBER_ERROR, "resuming transferred fiber");
  }
  if (status == MRB_FIBER_RUNNING || status == MRB_FIBER_RESUMED) {
    mrb_raise(mrb, E_FIBER_ERROR, "double resume");
  }
  if (status == MRB_FIBER_TERMINATED) {
    mrb_raise(mrb, E_FIBER_ERROR, "resuming dead fiber");
  }
  old_c->status = resume ? MRB_FIBER_RESUMED : MRB_FIBER_TRANSFERRED;
  c->prev = resume ? mrb->c : (c->prev ? c->prev : mrb->root_c);
  fiber_switch_context(mrb, c);
  if (status == MRB_FIBER_CREATED) {
    mrb_value *b, *e;

    if (!c->ci->proc) {
      mrb_raise(mrb, E_FIBER_ERROR, "double resume (current)");
    }
    mrb_stack_extend(mrb, len+2); /* for receiver and (optional) block */
    b = c->stack+1;
    e = b + len;
    while (b<e) {
      *b++ = *a++;
    }
    c->cibase->argc = (int)len;
    value = c->stack[0] = MRB_PROC_ENV(c->ci->proc)->stack[0];
  }
  else {
    value = fiber_result(mrb, a, len);
  }

  if (vmexec) {
    c->vmexec = TRUE;
    value = mrb_vm_exec(mrb, c->ci[-1].proc, c->ci->pc);
    mrb->c = old_c;
  }
  else {
    MARK_CONTEXT_MODIFY(c);
  }
  return value;
}