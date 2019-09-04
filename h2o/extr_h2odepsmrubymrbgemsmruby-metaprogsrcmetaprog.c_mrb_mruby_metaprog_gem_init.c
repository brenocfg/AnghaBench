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
struct TYPE_5__ {struct RClass* module_class; struct RClass* kernel_module; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_ARGS_ANY () ; 
 int /*<<< orphan*/  MRB_ARGS_NONE () ; 
 int /*<<< orphan*/  MRB_ARGS_OPT (int) ; 
 int /*<<< orphan*/  MRB_ARGS_REQ (int) ; 
 int /*<<< orphan*/  mod_define_singleton_method ; 
 int /*<<< orphan*/  mrb_define_class_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_f_global_variables ; 
 int /*<<< orphan*/  mrb_f_nil ; 
 int /*<<< orphan*/  mrb_f_send ; 
 int /*<<< orphan*/  mrb_local_variables ; 
 int /*<<< orphan*/  mrb_mod_class_variables ; 
 int /*<<< orphan*/  mrb_mod_constants ; 
 int /*<<< orphan*/  mrb_mod_cvar_defined ; 
 int /*<<< orphan*/  mrb_mod_cvar_get ; 
 int /*<<< orphan*/  mrb_mod_cvar_set ; 
 int /*<<< orphan*/  mrb_mod_included_modules ; 
 int /*<<< orphan*/  mrb_mod_instance_methods ; 
 int /*<<< orphan*/  mrb_mod_remove_cvar ; 
 int /*<<< orphan*/  mrb_mod_remove_method ; 
 int /*<<< orphan*/  mrb_mod_s_constants ; 
 int /*<<< orphan*/  mrb_mod_s_nesting ; 
 int /*<<< orphan*/  mrb_obj_instance_variables ; 
 int /*<<< orphan*/  mrb_obj_ivar_defined ; 
 int /*<<< orphan*/  mrb_obj_ivar_get ; 
 int /*<<< orphan*/  mrb_obj_ivar_set ; 
 int /*<<< orphan*/  mrb_obj_methods_m ; 
 int /*<<< orphan*/  mrb_obj_private_methods ; 
 int /*<<< orphan*/  mrb_obj_protected_methods ; 
 int /*<<< orphan*/  mrb_obj_public_methods ; 
 int /*<<< orphan*/  mrb_obj_singleton_methods_m ; 
 int /*<<< orphan*/  mrb_singleton_class ; 

void
mrb_mruby_metaprog_gem_init(mrb_state* mrb)
{
  struct RClass *krn = mrb->kernel_module;
  struct RClass *mod = mrb->module_class;

  mrb_define_method(mrb, krn, "global_variables", mrb_f_global_variables, MRB_ARGS_NONE()); /* 15.3.1.2.4 */
  mrb_define_method(mrb, krn, "local_variables", mrb_local_variables, MRB_ARGS_NONE()); /* 15.3.1.3.28 */

  mrb_define_method(mrb, krn, "singleton_class", mrb_singleton_class, MRB_ARGS_NONE());
  mrb_define_method(mrb, krn, "instance_variable_defined?", mrb_obj_ivar_defined, MRB_ARGS_REQ(1)); /* 15.3.1.3.20 */
  mrb_define_method(mrb, krn, "instance_variable_get", mrb_obj_ivar_get, MRB_ARGS_REQ(1)); /* 15.3.1.3.21 */
  mrb_define_method(mrb, krn, "instance_variable_set", mrb_obj_ivar_set, MRB_ARGS_REQ(2)); /* 15.3.1.3.22 */
  mrb_define_method(mrb, krn, "instance_variables", mrb_obj_instance_variables, MRB_ARGS_NONE()); /* 15.3.1.3.23 */
  mrb_define_method(mrb, krn, "methods", mrb_obj_methods_m, MRB_ARGS_OPT(1)); /* 15.3.1.3.31 */
  mrb_define_method(mrb, krn, "private_methods", mrb_obj_private_methods, MRB_ARGS_OPT(1)); /* 15.3.1.3.36 */
  mrb_define_method(mrb, krn, "protected_methods", mrb_obj_protected_methods, MRB_ARGS_OPT(1)); /* 15.3.1.3.37 */
  mrb_define_method(mrb, krn, "public_methods", mrb_obj_public_methods, MRB_ARGS_OPT(1)); /* 15.3.1.3.38 */
  mrb_define_method(mrb, krn, "singleton_methods", mrb_obj_singleton_methods_m, MRB_ARGS_OPT(1)); /* 15.3.1.3.45 */
  mrb_define_method(mrb, krn, "define_singleton_method", mod_define_singleton_method, MRB_ARGS_ANY());
  mrb_define_method(mrb, krn, "send", mrb_f_send, MRB_ARGS_ANY()); /* 15.3.1.3.44 */

  mrb_define_method(mrb, mod, "class_variables", mrb_mod_class_variables, MRB_ARGS_NONE()); /* 15.2.2.4.19 */
  mrb_define_method(mrb, mod, "remove_class_variable", mrb_mod_remove_cvar, MRB_ARGS_REQ(1)); /* 15.2.2.4.39 */
  mrb_define_method(mrb, mod, "class_variable_defined?", mrb_mod_cvar_defined, MRB_ARGS_REQ(1)); /* 15.2.2.4.16 */
  mrb_define_method(mrb, mod, "class_variable_get", mrb_mod_cvar_get, MRB_ARGS_REQ(1)); /* 15.2.2.4.17 */
  mrb_define_method(mrb, mod, "class_variable_set", mrb_mod_cvar_set, MRB_ARGS_REQ(2)); /* 15.2.2.4.18 */
  mrb_define_method(mrb, mod, "included_modules", mrb_mod_included_modules, MRB_ARGS_NONE()); /* 15.2.2.4.30 */
  mrb_define_method(mrb, mod, "instance_methods", mrb_mod_instance_methods, MRB_ARGS_ANY()); /* 15.2.2.4.33 */
  mrb_define_method(mrb, mod, "remove_method", mrb_mod_remove_method, MRB_ARGS_ANY()); /* 15.2.2.4.41 */
  mrb_define_method(mrb, mod, "method_removed", mrb_f_nil, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mod, "constants", mrb_mod_constants, MRB_ARGS_OPT(1)); /* 15.2.2.4.24 */
  mrb_define_class_method(mrb, mod, "constants", mrb_mod_s_constants, MRB_ARGS_ANY()); /* 15.2.2.3.1 */
  mrb_define_class_method(mrb, mod, "nesting", mrb_mod_s_nesting, MRB_ARGS_REQ(0)); /* 15.2.2.3.2 */
}