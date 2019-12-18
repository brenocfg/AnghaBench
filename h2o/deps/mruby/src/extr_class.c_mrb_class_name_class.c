#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct RObject {int dummy; } ;
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_sym ;
struct TYPE_9__ {struct RClass* object_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_class_path (TYPE_1__*,struct RClass*) ; 
 int /*<<< orphan*/  mrb_intern_lit (TYPE_1__*,char*) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_obj_iv_defined (TYPE_1__*,struct RObject*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_iv_set (TYPE_1__*,struct RObject*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RClass*) ; 
 int /*<<< orphan*/  mrb_str_cat_cstr (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 char* mrb_sym2name (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_symbol_value (int /*<<< orphan*/ ) ; 

void
mrb_class_name_class(mrb_state *mrb, struct RClass *outer, struct RClass *c, mrb_sym id)
{
  mrb_value name;
  mrb_sym nsym = mrb_intern_lit(mrb, "__classname__");

  if (mrb_obj_iv_defined(mrb, (struct RObject*)c, nsym)) return;
  if (outer == NULL || outer == mrb->object_class) {
    name = mrb_symbol_value(id);
  }
  else {
    name = mrb_class_path(mrb, outer);
    if (mrb_nil_p(name)) {      /* unnamed outer class */
      if (outer != mrb->object_class && outer != c) {
        mrb_obj_iv_set(mrb, (struct RObject*)c, mrb_intern_lit(mrb, "__outer__"),
                       mrb_obj_value(outer));
      }
      return;
    }
    mrb_str_cat_cstr(mrb, name, "::");
    mrb_str_cat_cstr(mrb, name, mrb_sym2name(mrb, id));
  }
  mrb_obj_iv_set(mrb, (struct RObject*)c, nsym, name);
}