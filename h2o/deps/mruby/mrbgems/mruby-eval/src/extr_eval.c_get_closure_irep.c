#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mrb_irep {int dummy; } ;
struct TYPE_8__ {struct mrb_irep* irep; } ;
struct RProc {TYPE_3__ body; struct RProc* upper; } ;
struct TYPE_9__ {TYPE_2__* c; } ;
typedef  TYPE_4__ mrb_state ;
struct TYPE_7__ {TYPE_1__* ci; } ;
struct TYPE_6__ {struct RProc* proc; } ;

/* Variables and functions */
 scalar_t__ MRB_PROC_CFUNC_P (struct RProc*) ; 

__attribute__((used)) static struct mrb_irep *
get_closure_irep(mrb_state *mrb, int level)
{
  struct RProc *proc = mrb->c->ci[-1].proc;

  while (level--) {
    if (!proc) return NULL;
    proc = proc->upper;
  }
  if (!proc) return NULL;
  if (MRB_PROC_CFUNC_P(proc)) {
    return NULL;
  }
  return proc->body.irep;
}