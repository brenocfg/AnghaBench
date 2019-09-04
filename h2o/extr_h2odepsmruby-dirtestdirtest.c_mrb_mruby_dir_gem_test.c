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
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_ARGS_NONE () ; 
 int /*<<< orphan*/  mrb_define_class_method (int /*<<< orphan*/ *,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct RClass* mrb_define_module (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_dirtest_sandbox ; 
 int /*<<< orphan*/  mrb_dirtest_setup ; 
 int /*<<< orphan*/  mrb_dirtest_teardown ; 

void
mrb_mruby_dir_gem_test(mrb_state *mrb)
{
  struct RClass *c = mrb_define_module(mrb, "DirTest");

  mrb_define_class_method(mrb, c, "sandbox", mrb_dirtest_sandbox, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, c, "setup", mrb_dirtest_setup, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, c, "teardown", mrb_dirtest_teardown, MRB_ARGS_NONE());
}