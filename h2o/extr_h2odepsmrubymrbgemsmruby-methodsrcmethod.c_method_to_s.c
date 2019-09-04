#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_class_name (int /*<<< orphan*/ *,struct RClass*) ; 
 struct RClass* mrb_class_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_iv_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_classname (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_cat_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_cat_lit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_str_cat_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new_lit (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static mrb_value
method_to_s(mrb_state *mrb, mrb_value self)
{
  mrb_value owner = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@owner"));
  mrb_value klass = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@klass"));
  mrb_value name = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@name"));
  mrb_value str = mrb_str_new_lit(mrb, "#<");
  struct RClass *rklass;

  mrb_str_cat_cstr(mrb, str, mrb_obj_classname(mrb, self));
  mrb_str_cat_lit(mrb, str, ": ");
  rklass = mrb_class_ptr(klass);
  if (mrb_class_ptr(owner) == rklass) {
    mrb_str_cat_str(mrb, str, mrb_funcall(mrb, owner, "to_s", 0));
    mrb_str_cat_lit(mrb, str, "#");
    mrb_str_cat_str(mrb, str, mrb_funcall(mrb, name, "to_s", 0));
  }
  else {
    mrb_str_cat_cstr(mrb, str, mrb_class_name(mrb, rklass));
    mrb_str_cat_lit(mrb, str, "(");
    mrb_str_cat_str(mrb, str, mrb_funcall(mrb, owner, "to_s", 0));
    mrb_str_cat_lit(mrb, str, ")#");
    mrb_str_cat_str(mrb, str, mrb_funcall(mrb, name, "to_s", 0));
  }
  mrb_str_cat_lit(mrb, str, ">");
  return str;
}