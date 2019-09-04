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
struct RProc {int /*<<< orphan*/ * c; } ;
struct TYPE_3__ {scalar_t__ no_exec; scalar_t__ dump_result; } ;
typedef  TYPE_1__ mrbc_context ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_irep ;

/* Variables and functions */
 int /*<<< orphan*/  irep_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_codedump_all (int /*<<< orphan*/ *,struct RProc*) ; 
 int /*<<< orphan*/  mrb_irep_decref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_obj_value (struct RProc*) ; 
 struct RProc* mrb_proc_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_top_run (int /*<<< orphan*/ *,struct RProc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_top_self (int /*<<< orphan*/ *) ; 

__attribute__((used)) static mrb_value
load_irep(mrb_state *mrb, mrb_irep *irep, mrbc_context *c)
{
  struct RProc *proc;

  if (!irep) {
    irep_error(mrb);
    return mrb_nil_value();
  }
  proc = mrb_proc_new(mrb, irep);
  proc->c = NULL;
  mrb_irep_decref(mrb, irep);
  if (c && c->dump_result) mrb_codedump_all(mrb, proc);
  if (c && c->no_exec) return mrb_obj_value(proc);
  return mrb_top_run(mrb, proc, mrb_top_self(mrb), 0);
}