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
typedef  enum mrb_vtype { ____Placeholder_mrb_vtype } mrb_vtype ;

/* Variables and functions */
 int MRB_INSTANCE_TT (struct RClass*) ; 
 int MRB_TT_OBJECT ; 
 struct RClass* mrb_class_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_io_initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_obj_alloc (int /*<<< orphan*/ *,int,struct RClass*) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RObject*) ; 

mrb_value
mrb_io_s_for_fd(mrb_state *mrb, mrb_value klass)
{
  struct RClass *c = mrb_class_ptr(klass);
  enum mrb_vtype ttype = MRB_INSTANCE_TT(c);
  mrb_value obj;

  /* copied from mrb_instance_alloc() */
  if (ttype == 0) ttype = MRB_TT_OBJECT;
  obj = mrb_obj_value((struct RObject*)mrb_obj_alloc(mrb, ttype, c));
  return mrb_io_initialize(mrb, obj);
}