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
struct TYPE_2__ {scalar_t__ func; scalar_t__ irep; } ;
struct RProc {TYPE_1__ body; } ;
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  IV_GET (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ MRB_PROC_CFUNC_P (struct RProc*) ; 
 scalar_t__ mrb_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct RClass* mrb_class_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_false_value () ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_is_instance_of (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 struct RProc* mrb_proc_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_true_value () ; 

__attribute__((used)) static mrb_value
method_eql(mrb_state *mrb, mrb_value self)
{
  mrb_value other, receiver, orig_proc, other_proc;
  struct RClass *owner, *klass;
  struct RProc *orig_rproc, *other_rproc;

  mrb_get_args(mrb, "o", &other);
  if (!mrb_obj_is_instance_of(mrb, other, mrb_class(mrb, self)))
    return mrb_false_value();

  if (mrb_class(mrb, self) != mrb_class(mrb, other))
    return mrb_false_value();

  klass = mrb_class_ptr(IV_GET(self, "@klass"));
  if (klass != mrb_class_ptr(IV_GET(other, "@klass")))
    return mrb_false_value();

  owner = mrb_class_ptr(IV_GET(self, "@owner"));
  if (owner != mrb_class_ptr(IV_GET(other, "@owner")))
    return mrb_false_value();

  receiver = IV_GET(self, "@recv");
  if (!mrb_obj_equal(mrb, receiver, IV_GET(other, "@recv")))
    return mrb_false_value();

  orig_proc = IV_GET(self, "proc");
  other_proc = IV_GET(other, "proc");
  if (mrb_nil_p(orig_proc) && mrb_nil_p(other_proc)) {
    if (mrb_symbol(IV_GET(self, "@name")) == mrb_symbol(IV_GET(other, "@name")))
      return mrb_true_value();
    else
      return mrb_false_value();
  }

  if (mrb_nil_p(orig_proc))
    return mrb_false_value();
  if (mrb_nil_p(other_proc))
    return mrb_false_value();

  orig_rproc = mrb_proc_ptr(orig_proc);
  other_rproc = mrb_proc_ptr(other_proc);
  if (MRB_PROC_CFUNC_P(orig_rproc)) {
    if (!MRB_PROC_CFUNC_P(other_rproc))
      return mrb_false_value();
    if (orig_rproc->body.func != other_rproc->body.func)
      return mrb_false_value();
  }
  else {
    if (MRB_PROC_CFUNC_P(other_rproc))
      return mrb_false_value();
    if (orig_rproc->body.irep != other_rproc->body.irep)
      return mrb_false_value();
  }

  return mrb_true_value();
}