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
typedef  int /*<<< orphan*/  const mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_bool (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  const mrb_bool_value (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_obj_iv_set (int /*<<< orphan*/ *,struct RObject*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  onig_regexp_clear_global_variables (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 

__attribute__((used)) static mrb_value
onig_regexp_set_set_global_variables(mrb_state* mrb, mrb_value self) {
  mrb_value arg;
  mrb_get_args(mrb, "o", &arg);
  mrb_value const ret = mrb_bool_value(mrb_bool(arg));
  mrb_obj_iv_set(mrb, (struct RObject*)mrb_class_get(mrb, "OnigRegexp"),
                 mrb_intern_lit(mrb, "@set_global_variables"), ret);
  onig_regexp_clear_global_variables(mrb, self);
  return ret;
}