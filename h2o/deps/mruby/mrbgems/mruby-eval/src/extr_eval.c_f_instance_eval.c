#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct RProc {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_12__ {TYPE_2__* c; } ;
typedef  TYPE_3__ mrb_state ;
typedef  int mrb_int ;
struct TYPE_11__ {TYPE_1__* ci; } ;
struct TYPE_10__ {int /*<<< orphan*/  target_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_PROC_CFUNC_P (struct RProc*) ; 
 int /*<<< orphan*/  MRB_PROC_SET_TARGET_CLASS (struct RProc*,int /*<<< orphan*/ ) ; 
 struct RProc* create_proc_from_string (TYPE_3__*,char*,int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  exec_irep (TYPE_3__*,int /*<<< orphan*/ ,struct RProc*) ; 
 int /*<<< orphan*/  mrb_assert (int) ; 
 int /*<<< orphan*/  mrb_class_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (TYPE_3__*,char*,char**,...) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_obj_instance_eval (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_singleton_class (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
f_instance_eval(mrb_state *mrb, mrb_value self)
{
  mrb_value b;
  mrb_int argc; mrb_value *argv;

  mrb_get_args(mrb, "*!&", &argv, &argc, &b);

  if (mrb_nil_p(b)) {
    char *s;
    mrb_int len;
    char *file = NULL;
    mrb_int line = 1;
    mrb_value cv;
    struct RProc *proc;

    mrb_get_args(mrb, "s|zi", &s, &len, &file, &line);
    cv = mrb_singleton_class(mrb, self);
    proc = create_proc_from_string(mrb, s, len, mrb_nil_value(), file, line);
    MRB_PROC_SET_TARGET_CLASS(proc, mrb_class_ptr(cv));
    mrb_assert(!MRB_PROC_CFUNC_P(proc));
    mrb->c->ci->target_class = mrb_class_ptr(cv);
    return exec_irep(mrb, self, proc);
  }
  else {
    mrb_get_args(mrb, "&", &b);
    return mrb_obj_instance_eval(mrb, self);
  }
}