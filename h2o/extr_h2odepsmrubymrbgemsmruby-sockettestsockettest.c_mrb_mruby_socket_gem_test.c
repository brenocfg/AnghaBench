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
 int /*<<< orphan*/  mrb_sockettest_cygwin_p ; 
 int /*<<< orphan*/  mrb_sockettest_tmppath ; 
 int /*<<< orphan*/  mrb_sockettest_win_p ; 

void
mrb_mruby_socket_gem_test(mrb_state* mrb)
{
  struct RClass *c = mrb_define_module(mrb, "SocketTest");
  mrb_define_class_method(mrb, c, "tmppath", mrb_sockettest_tmppath, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, c, "win?", mrb_sockettest_win_p, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, c, "cygwin?", mrb_sockettest_cygwin_p, MRB_ARGS_NONE());
}