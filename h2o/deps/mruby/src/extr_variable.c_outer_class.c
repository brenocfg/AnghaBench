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
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
#define  MRB_TT_CLASS 129 
#define  MRB_TT_MODULE 128 
 struct RClass* mrb_class_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_iv_get (int /*<<< orphan*/ *,struct RObject*,int /*<<< orphan*/ ) ; 
 int mrb_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct RClass*
outer_class(mrb_state *mrb, struct RClass *c)
{
  mrb_value ov;

  ov = mrb_obj_iv_get(mrb, (struct RObject*)c, mrb_intern_lit(mrb, "__outer__"));
  if (mrb_nil_p(ov)) return NULL;
  switch (mrb_type(ov)) {
  case MRB_TT_CLASS:
  case MRB_TT_MODULE:
    return mrb_class_ptr(ov);
  default:
    break;
  }
  return NULL;
}