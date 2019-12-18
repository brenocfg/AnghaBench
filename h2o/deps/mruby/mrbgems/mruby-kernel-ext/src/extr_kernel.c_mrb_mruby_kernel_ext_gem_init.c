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
struct TYPE_5__ {struct RClass* kernel_module; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_ARGS_ANY () ; 
 int /*<<< orphan*/  MRB_ARGS_NONE () ; 
 int /*<<< orphan*/  MRB_ARGS_OPT (int) ; 
 int /*<<< orphan*/  MRB_ARGS_REQ (int) ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_module_function (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_f_array ; 
 int /*<<< orphan*/  mrb_f_caller ; 
 int /*<<< orphan*/  mrb_f_float ; 
 int /*<<< orphan*/  mrb_f_hash ; 
 int /*<<< orphan*/  mrb_f_integer ; 
 int /*<<< orphan*/  mrb_f_itself ; 
 int /*<<< orphan*/  mrb_f_method ; 
 int /*<<< orphan*/  mrb_f_raise ; 
 int /*<<< orphan*/  mrb_f_string ; 

void
mrb_mruby_kernel_ext_gem_init(mrb_state *mrb)
{
  struct RClass *krn = mrb->kernel_module;

  mrb_define_module_function(mrb, krn, "fail", mrb_f_raise, MRB_ARGS_OPT(2));
  mrb_define_module_function(mrb, krn, "caller", mrb_f_caller, MRB_ARGS_OPT(2));
  mrb_define_method(mrb, krn, "__method__", mrb_f_method, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, krn, "Integer", mrb_f_integer, MRB_ARGS_ANY());
#ifndef MRB_WITHOUT_FLOAT
  mrb_define_module_function(mrb, krn, "Float", mrb_f_float, MRB_ARGS_REQ(1));
#endif
  mrb_define_module_function(mrb, krn, "String", mrb_f_string, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, krn, "Array", mrb_f_array, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, krn, "Hash", mrb_f_hash, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, krn, "itself", mrb_f_itself, MRB_ARGS_NONE());
}