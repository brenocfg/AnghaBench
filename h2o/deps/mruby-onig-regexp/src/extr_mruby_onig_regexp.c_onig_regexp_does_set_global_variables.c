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
 scalar_t__ mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_obj_iv_get (int /*<<< orphan*/ *,struct RObject*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
onig_regexp_does_set_global_variables(mrb_state* mrb, mrb_value self) {
  (void)self;
  return mrb_obj_iv_get(mrb, (struct RObject*)mrb_class_get(mrb, "OnigRegexp"),
                        mrb_intern_lit(mrb, "@set_global_variables"));
}