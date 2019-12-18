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
struct RProc {int const tt; struct RProc* c; struct RProc* super; } ;
struct RObject {int const tt; struct RObject* c; struct RObject* super; } ;
struct RClass {int const tt; struct RClass* c; struct RClass* super; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_2__ {struct RProc* super; } ;

/* Variables and functions */
#define  MRB_TT_ICLASS 129 
#define  MRB_TT_SCLASS 128 
 struct RProc* method_object_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct RProc* method_search_vm (int /*<<< orphan*/ *,struct RProc**,int /*<<< orphan*/ ) ; 
 TYPE_1__* mrb_class_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_iv_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_obj_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_iv_set (int /*<<< orphan*/ *,struct RProc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RProc*) ; 
 int /*<<< orphan*/  mrb_symbol (int /*<<< orphan*/ ) ; 
 int mrb_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
method_super_method(mrb_state *mrb, mrb_value self)
{
  mrb_value recv = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@recv"));
  mrb_value klass = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@klass"));
  mrb_value owner = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@owner"));
  mrb_value name = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@name"));
  struct RClass *super, *rklass;
  struct RProc *proc;
  struct RObject *me;

  switch (mrb_type(klass)) {
    case MRB_TT_SCLASS:
      super = mrb_class_ptr(klass)->super->super;
      break;
    case MRB_TT_ICLASS:
      super = mrb_class_ptr(klass)->super;
      break;
    default:
      super = mrb_class_ptr(owner)->super;
      break;
  }

  proc = method_search_vm(mrb, &super, mrb_symbol(name));
  if (!proc)
    return mrb_nil_value();

  rklass = super;
  while (super->tt == MRB_TT_ICLASS)
    super = super->c;

  me = method_object_alloc(mrb, mrb_obj_class(mrb, self));
  mrb_obj_iv_set(mrb, me, mrb_intern_lit(mrb, "@owner"), mrb_obj_value(super));
  mrb_obj_iv_set(mrb, me, mrb_intern_lit(mrb, "@recv"), recv);
  mrb_obj_iv_set(mrb, me, mrb_intern_lit(mrb, "@name"), name);
  mrb_obj_iv_set(mrb, me, mrb_intern_lit(mrb, "proc"), mrb_obj_value(proc));
  mrb_obj_iv_set(mrb, me, mrb_intern_lit(mrb, "@klass"), mrb_obj_value(rklass));

  return mrb_obj_value(me);
}