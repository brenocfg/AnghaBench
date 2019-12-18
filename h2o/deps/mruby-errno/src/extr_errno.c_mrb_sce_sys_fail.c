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
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;
struct TYPE_2__ {struct RClass* c; } ;

/* Variables and functions */
 TYPE_1__* mrb_basic_ptr (int /*<<< orphan*/ ) ; 
 struct RClass* mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 struct RClass* mrb_define_class_under (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct RClass*) ; 
 int /*<<< orphan*/  mrb_define_const (int /*<<< orphan*/ *,struct RClass*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_exc_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (scalar_t__) ; 
 int /*<<< orphan*/  mrb_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,...) ; 
 int mrb_get_args (int /*<<< orphan*/ *,char*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_module_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 struct RClass* mrb_obj_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RClass*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,long) ; 

__attribute__((used)) static mrb_value
mrb_sce_sys_fail(mrb_state *mrb, mrb_value cls)
{
  struct RClass *cl, *sce;
  mrb_value e, msg;
  mrb_int no;
  int argc;
  char name[8];

  sce = mrb_class_get(mrb, "SystemCallError");
  argc = mrb_get_args(mrb, "i|S", &no, &msg);
  if (argc == 1) {
    e = mrb_funcall(mrb, mrb_obj_value(sce), "new", 1, mrb_fixnum_value(no));
  } else {
    e = mrb_funcall(mrb, mrb_obj_value(sce), "new", 2, msg, mrb_fixnum_value(no));
  }
  if (mrb_obj_class(mrb, e) == sce) {
    snprintf(name, sizeof(name), "E%03ld", (long)no);
    cl = mrb_define_class_under(mrb, mrb_module_get(mrb, "Errno"), name, sce);
    mrb_define_const(mrb, cl, "Errno", mrb_fixnum_value(no));
    mrb_basic_ptr(e)->c = cl;
  }
  mrb_exc_raise(mrb, e);
  return mrb_nil_value();  /* NOTREACHED */
}