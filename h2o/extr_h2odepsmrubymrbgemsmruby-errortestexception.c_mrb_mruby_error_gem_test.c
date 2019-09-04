#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct RClass {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  object_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int MRB_ARGS_BLOCK () ; 
 int MRB_ARGS_NONE () ; 
 int MRB_ARGS_REQ (int) ; 
 struct RClass* mrb_define_class (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_module_function (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  run_ensure ; 
 int /*<<< orphan*/  run_protect ; 
 int /*<<< orphan*/  run_rescue ; 
 int /*<<< orphan*/  run_rescue_exceptions ; 

void
mrb_mruby_error_gem_test(mrb_state *mrb)
{
  struct RClass *cls;

  cls = mrb_define_class(mrb, "ExceptionTest", mrb->object_class);
  mrb_define_module_function(mrb, cls, "mrb_protect", run_protect, MRB_ARGS_NONE() | MRB_ARGS_BLOCK());
  mrb_define_module_function(mrb, cls, "mrb_ensure", run_ensure, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, cls, "mrb_rescue", run_rescue, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, cls, "mrb_rescue_exceptions", run_rescue_exceptions, MRB_ARGS_REQ(2));
}