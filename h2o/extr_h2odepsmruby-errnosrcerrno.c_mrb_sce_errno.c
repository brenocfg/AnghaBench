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
 int /*<<< orphan*/  mrb_attr_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct RClass* mrb_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_const_defined_at (int /*<<< orphan*/ *,struct RClass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_const_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RClass*) ; 

__attribute__((used)) static mrb_value
mrb_sce_errno(mrb_state *mrb, mrb_value self)
{
  struct RClass *c;
  mrb_sym sym;

  c = mrb_class(mrb, self);
  sym = mrb_intern_lit(mrb, "Errno");
#if MRUBY_RELEASE_NO < 10000
  if (mrb_const_defined_at(mrb, c, sym)) {
#else
  if (mrb_const_defined_at(mrb, mrb_obj_value(c), sym)) {
#endif
    return mrb_const_get(mrb, mrb_obj_value(c), sym);
  } else {
    sym = mrb_intern_lit(mrb, "errno");
    return mrb_attr_get(mrb, self, sym);
  }
}