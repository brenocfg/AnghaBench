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
struct RClass {struct RClass* super; } ;
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  E_TYPE_ERROR ; 
 int /*<<< orphan*/  MRB_CLASS_ORIGIN (struct RClass*) ; 
 struct RClass* class_from_sym (int /*<<< orphan*/ *,struct RClass*,int /*<<< orphan*/ ) ; 
 struct RClass* mrb_class_new (int /*<<< orphan*/ *,struct RClass*) ; 
 struct RClass* mrb_class_real (struct RClass*) ; 
 scalar_t__ mrb_const_defined_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RClass*) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_sym2str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_class (int /*<<< orphan*/ *,struct RClass*,struct RClass*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct RClass*
define_class(mrb_state *mrb, mrb_sym name, struct RClass *super, struct RClass *outer)
{
  struct RClass * c;

  if (mrb_const_defined_at(mrb, mrb_obj_value(outer), name)) {
    c = class_from_sym(mrb, outer, name);
    MRB_CLASS_ORIGIN(c);
    if (super && mrb_class_real(c->super) != super) {
      mrb_raisef(mrb, E_TYPE_ERROR, "superclass mismatch for Class %S (%S not %S)",
                 mrb_sym2str(mrb, name),
                 mrb_obj_value(c->super), mrb_obj_value(super));
    }
    return c;
  }

  c = mrb_class_new(mrb, super);
  setup_class(mrb, outer, c, name);

  return c;
}