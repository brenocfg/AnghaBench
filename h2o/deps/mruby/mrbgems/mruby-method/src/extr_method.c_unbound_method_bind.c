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
struct RObject {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  E_TYPE_ERROR ; 
 scalar_t__ MRB_TT_MODULE ; 
 scalar_t__ MRB_TT_SCLASS ; 
 struct RObject* method_object_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 char* mrb_class_name (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ mrb_class_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_iv_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_obj_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_is_kind_of (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mrb_obj_iv_set (int /*<<< orphan*/ *,struct RObject*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RObject*) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new_static (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static mrb_value
unbound_method_bind(mrb_state *mrb, mrb_value self)
{
  struct RObject *me;
  mrb_value owner = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@owner"));
  mrb_value name = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@name"));
  mrb_value proc = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "proc"));
  mrb_value klass = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@klass"));
  mrb_value recv;

  mrb_get_args(mrb, "o", &recv);

  if (mrb_type(owner) != MRB_TT_MODULE &&
      mrb_class_ptr(owner) != mrb_obj_class(mrb, recv) &&
      !mrb_obj_is_kind_of(mrb, recv, mrb_class_ptr(owner))) {
        if (mrb_type(owner) == MRB_TT_SCLASS) {
          mrb_raise(mrb, E_TYPE_ERROR, "singleton method called for a different object");
        } else {
          const char *s = mrb_class_name(mrb, mrb_class_ptr(owner));
          mrb_raisef(mrb, E_TYPE_ERROR, "bind argument must be an instance of %S", mrb_str_new_static(mrb, s, strlen(s)));
        }
  }
  me = method_object_alloc(mrb, mrb_class_get(mrb, "Method"));
  mrb_obj_iv_set(mrb, me, mrb_intern_lit(mrb, "@owner"), owner);
  mrb_obj_iv_set(mrb, me, mrb_intern_lit(mrb, "@recv"), recv);
  mrb_obj_iv_set(mrb, me, mrb_intern_lit(mrb, "@name"), name);
  mrb_obj_iv_set(mrb, me, mrb_intern_lit(mrb, "proc"), proc);
  mrb_obj_iv_set(mrb, me, mrb_intern_lit(mrb, "@klass"), klass);

  return mrb_obj_value(me);
}