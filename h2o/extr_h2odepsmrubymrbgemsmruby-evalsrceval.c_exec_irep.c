#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct RProc {int dummy; } ;
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_10__ {TYPE_2__* c; scalar_t__ exc; } ;
typedef  TYPE_3__ mrb_state ;
struct TYPE_9__ {int /*<<< orphan*/ * stack; TYPE_1__* cibase; TYPE_1__* ci; } ;
struct TYPE_8__ {scalar_t__ acc; scalar_t__ argc; } ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_exc_raise (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_exec_irep (TYPE_3__*,int /*<<< orphan*/ ,struct RProc*) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_obj_value (scalar_t__) ; 
 int /*<<< orphan*/  mrb_top_run (TYPE_3__*,struct RProc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
exec_irep(mrb_state *mrb, mrb_value self, struct RProc *proc)
{
  /* no argument passed from eval() */
  mrb->c->ci->argc = 0;
  if (mrb->c->ci->acc < 0) {
    ptrdiff_t cioff = mrb->c->ci - mrb->c->cibase;
    mrb_value ret = mrb_top_run(mrb, proc, self, 0);
    if (mrb->exc) {
      mrb_exc_raise(mrb, mrb_obj_value(mrb->exc));
    }
    mrb->c->ci = mrb->c->cibase + cioff;
    return ret;
  }
  /* clear block */
  mrb->c->stack[1] = mrb_nil_value();
  return mrb_exec_irep(mrb, self, proc);
}