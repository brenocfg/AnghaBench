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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  OnigRegex ;

/* Variables and functions */
 int /*<<< orphan*/  Data_Get_Struct (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_RUNTIME_ERROR ; 
 int /*<<< orphan*/  mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_false_value () ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_iv_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_obj_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_is_kind_of (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_onig_regexp_type ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mrb_str_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_true_value () ; 
 scalar_t__ onig_get_options (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
onig_regexp_equal(mrb_state *mrb, mrb_value self) {
  mrb_value other;
  OnigRegex self_reg, other_reg;

  mrb_get_args(mrb, "o", &other);
  if (mrb_obj_equal(mrb, self, other)){
    return mrb_true_value();
  }
  if (mrb_nil_p(other)) {
    return mrb_false_value();
  }
  if (!mrb_obj_is_kind_of(mrb, other, mrb_class_get(mrb, "OnigRegexp"))) {
    return mrb_false_value();
  }
  Data_Get_Struct(mrb, self, &mrb_onig_regexp_type, self_reg);
  Data_Get_Struct(mrb, other, &mrb_onig_regexp_type, other_reg);

  if (!self_reg || !other_reg){
      mrb_raise(mrb, E_RUNTIME_ERROR, "Invalid OnigRegexp");
  }
  if (onig_get_options(self_reg) != onig_get_options(other_reg)){
      return mrb_false_value();
  }
  return mrb_str_equal(mrb, mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@source")), mrb_iv_get(mrb, other, mrb_intern_lit(mrb, "@source"))) ?
      mrb_true_value() : mrb_false_value();
}