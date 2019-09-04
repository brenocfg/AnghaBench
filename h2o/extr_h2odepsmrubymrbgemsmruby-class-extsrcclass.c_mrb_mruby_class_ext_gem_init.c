#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct RClass {int dummy; } ;
struct TYPE_4__ {struct RClass* module_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int MRB_ARGS_ANY () ; 
 int MRB_ARGS_BLOCK () ; 
 int MRB_ARGS_NONE () ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_mod_module_exec ; 
 int /*<<< orphan*/  mrb_mod_name ; 
 int /*<<< orphan*/  mrb_mod_singleton_class_p ; 

void
mrb_mruby_class_ext_gem_init(mrb_state *mrb)
{
  struct RClass *mod = mrb->module_class;

  mrb_define_method(mrb, mod, "name", mrb_mod_name, MRB_ARGS_NONE());
  mrb_define_method(mrb, mod, "singleton_class?", mrb_mod_singleton_class_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, mod, "module_exec", mrb_mod_module_exec, MRB_ARGS_ANY()|MRB_ARGS_BLOCK());
  mrb_define_method(mrb, mod, "class_exec", mrb_mod_module_exec, MRB_ARGS_ANY()|MRB_ARGS_BLOCK());
}