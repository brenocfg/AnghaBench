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
 int /*<<< orphan*/  mrb_c_method ; 
 int /*<<< orphan*/  mrb_define_class_method (int /*<<< orphan*/ *,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct RClass* mrb_define_module (int /*<<< orphan*/ *,char*) ; 

void
mrb_c_and_ruby_extension_example_gem_init(mrb_state* mrb) {
  struct RClass *class_cextension = mrb_define_module(mrb, "CRubyExtension");
  mrb_define_class_method(mrb, class_cextension, "c_method", mrb_c_method, MRB_ARGS_NONE());
}