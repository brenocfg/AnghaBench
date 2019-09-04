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
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 struct RClass* module_from_sym (int /*<<< orphan*/ *,struct RClass*,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_const_defined_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct RClass* mrb_module_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RClass*) ; 
 int /*<<< orphan*/  setup_class (int /*<<< orphan*/ *,struct RClass*,struct RClass*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct RClass*
define_module(mrb_state *mrb, mrb_sym name, struct RClass *outer)
{
  struct RClass *m;

  if (mrb_const_defined_at(mrb, mrb_obj_value(outer), name)) {
    return module_from_sym(mrb, outer, name);
  }
  m = mrb_module_new(mrb);
  setup_class(mrb, outer, m, name);

  return m;
}