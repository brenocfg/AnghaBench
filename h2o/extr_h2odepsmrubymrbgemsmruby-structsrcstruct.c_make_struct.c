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
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_ARGS_ANY () ; 
 int /*<<< orphan*/  MRB_ARGS_NONE () ; 
 int /*<<< orphan*/  MRB_SET_INSTANCE_TT (struct RClass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRB_TT_ARRAY ; 
 int /*<<< orphan*/  RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_const_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_struct_define_accessors (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct RClass*) ; 
 struct RClass* mrb_class_new (int /*<<< orphan*/ *,struct RClass*) ; 
 scalar_t__ mrb_const_defined_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_const_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_class_method (int /*<<< orphan*/ *,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct RClass* mrb_define_class_under (int /*<<< orphan*/ *,struct RClass*,int /*<<< orphan*/ ,struct RClass*) ; 
 int /*<<< orphan*/  mrb_instance_new ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_iv_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_name_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_to_sym (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RClass*) ; 
 int /*<<< orphan*/  mrb_struct_s_members_m ; 
 int /*<<< orphan*/  mrb_sym2name_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_to_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
make_struct(mrb_state *mrb, mrb_value name, mrb_value members, struct RClass *klass)
{
  mrb_value nstr;
  mrb_sym id;
  struct RClass *c;

  if (mrb_nil_p(name)) {
    c = mrb_class_new(mrb, klass);
  }
  else {
    /* old style: should we warn? */
    mrb_to_str(mrb, name);
    id = mrb_obj_to_sym(mrb, name);
    if (!is_const_id(mrb, mrb_sym2name_len(mrb, id, NULL))) {
      mrb_name_error(mrb, id, "identifier %S needs to be constant", name);
    }
    if (mrb_const_defined_at(mrb, mrb_obj_value(klass), id)) {
      mrb_warn(mrb, "redefining constant Struct::%S", name);
      mrb_const_remove(mrb, mrb_obj_value(klass), id);
    }
    c = mrb_define_class_under(mrb, klass, RSTRING_PTR(name), klass);
  }
  MRB_SET_INSTANCE_TT(c, MRB_TT_ARRAY);
  nstr = mrb_obj_value(c);
  mrb_iv_set(mrb, nstr, mrb_intern_lit(mrb, "__members__"), members);

  mrb_define_class_method(mrb, c, "new", mrb_instance_new, MRB_ARGS_ANY());
  mrb_define_class_method(mrb, c, "[]", mrb_instance_new, MRB_ARGS_ANY());
  mrb_define_class_method(mrb, c, "members", mrb_struct_s_members_m, MRB_ARGS_NONE());
  /* RSTRUCT(nstr)->basic.c->super = c->c; */
  make_struct_define_accessors(mrb, members, c);
  return nstr;
}