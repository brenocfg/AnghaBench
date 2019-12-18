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
 int /*<<< orphan*/  MRB_ARGS_NONE () ; 
 int /*<<< orphan*/  MRB_ARGS_REQ (int) ; 
 struct RClass* mrb_define_class (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_module_function (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_system ; 
 int /*<<< orphan*/  test_win_p ; 

void mrb_mruby_file_stat_gem_test(mrb_state *mrb)
{
  struct RClass *t;

  t = mrb_define_class(mrb, "FileStatTest", mrb->object_class);
  mrb_define_module_function(mrb, t, "system", test_system, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, t, "win?", test_win_p, MRB_ARGS_NONE());
}