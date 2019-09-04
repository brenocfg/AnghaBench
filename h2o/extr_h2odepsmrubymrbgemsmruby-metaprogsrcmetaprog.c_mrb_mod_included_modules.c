#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct RClass {scalar_t__ tt; struct RClass* super; TYPE_1__* c; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_2__ {scalar_t__ tt; } ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_CLASS_ORIGIN (struct RClass*) ; 
 scalar_t__ MRB_TT_ICLASS ; 
 scalar_t__ MRB_TT_MODULE ; 
 int /*<<< orphan*/  mrb_ary_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct RClass* mrb_class_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (TYPE_1__*) ; 

__attribute__((used)) static mrb_value
mrb_mod_included_modules(mrb_state *mrb, mrb_value self)
{
  mrb_value result;
  struct RClass *c = mrb_class_ptr(self);
  struct RClass *origin = c;

  MRB_CLASS_ORIGIN(origin);
  result = mrb_ary_new(mrb);
  while (c) {
    if (c != origin && c->tt == MRB_TT_ICLASS) {
      if (c->c->tt == MRB_TT_MODULE) {
        mrb_ary_push(mrb, result, mrb_obj_value(c->c));
      }
    }
    c = c->super;
  }

  return result;
}