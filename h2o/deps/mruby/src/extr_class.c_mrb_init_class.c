#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct RObject {int dummy; } ;
struct RClass {struct RClass* c; } ;
struct TYPE_14__ {struct RObject* top_self; struct RClass* object_class; struct RClass* proc_class; struct RClass* class_class; struct RClass* module_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_ARGS_ANY () ; 
 int /*<<< orphan*/  MRB_ARGS_ARG (int,int) ; 
 int /*<<< orphan*/  MRB_ARGS_NONE () ; 
 int /*<<< orphan*/  MRB_ARGS_OPT (int) ; 
 int /*<<< orphan*/  MRB_ARGS_REQ (int) ; 
 int /*<<< orphan*/  MRB_SET_INSTANCE_TT (struct RClass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRB_TT_CLASS ; 
 int /*<<< orphan*/  MRB_TT_MODULE ; 
 int /*<<< orphan*/  MRB_TT_OBJECT ; 
 int /*<<< orphan*/  MRB_TT_PROC ; 
 struct RClass* boot_defclass (TYPE_1__*,struct RClass*) ; 
 int /*<<< orphan*/  inspect_main ; 
 int /*<<< orphan*/  make_metaclass (TYPE_1__*,struct RClass*) ; 
 int /*<<< orphan*/  mod_define_method ; 
 int /*<<< orphan*/  mrb_bob_init ; 
 int /*<<< orphan*/  mrb_bob_not ; 
 int /*<<< orphan*/  mrb_class_initialize ; 
 int /*<<< orphan*/  mrb_class_name_class (TYPE_1__*,int /*<<< orphan*/ *,struct RClass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_class_new_class ; 
 int /*<<< orphan*/  mrb_class_superclass ; 
 struct RClass* mrb_define_class (TYPE_1__*,char*,struct RClass*) ; 
 int /*<<< orphan*/  mrb_define_class_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_const (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_singleton_method (TYPE_1__*,struct RObject*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_f_send ; 
 int /*<<< orphan*/  mrb_instance_new ; 
 int /*<<< orphan*/  mrb_intern_lit (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mrb_mod_alias ; 
 int /*<<< orphan*/  mrb_mod_ancestors ; 
 int /*<<< orphan*/  mrb_mod_append_features ; 
 int /*<<< orphan*/  mrb_mod_attr_reader ; 
 int /*<<< orphan*/  mrb_mod_attr_writer ; 
 int /*<<< orphan*/  mrb_mod_const_defined ; 
 int /*<<< orphan*/  mrb_mod_const_get ; 
 int /*<<< orphan*/  mrb_mod_const_missing ; 
 int /*<<< orphan*/  mrb_mod_const_set ; 
 int /*<<< orphan*/  mrb_mod_dummy_visibility ; 
 int /*<<< orphan*/  mrb_mod_eqq ; 
 int /*<<< orphan*/  mrb_mod_extend_object ; 
 int /*<<< orphan*/  mrb_mod_include_p ; 
 int /*<<< orphan*/  mrb_mod_initialize ; 
 int /*<<< orphan*/  mrb_mod_method_defined ; 
 int /*<<< orphan*/  mrb_mod_module_eval ; 
 int /*<<< orphan*/  mrb_mod_module_function ; 
 int /*<<< orphan*/  mrb_mod_prepend_features ; 
 int /*<<< orphan*/  mrb_mod_remove_const ; 
 int /*<<< orphan*/  mrb_mod_to_s ; 
 int /*<<< orphan*/  mrb_mod_undef ; 
 scalar_t__ mrb_obj_alloc (TYPE_1__*,int /*<<< orphan*/ ,struct RClass*) ; 
 int /*<<< orphan*/  mrb_obj_equal_m ; 
 int /*<<< orphan*/  mrb_obj_id_m ; 
 int /*<<< orphan*/  mrb_obj_instance_eval ; 
 int /*<<< orphan*/  mrb_obj_not_equal_m ; 
 int /*<<< orphan*/  mrb_obj_value (struct RClass*) ; 
 int /*<<< orphan*/  mrb_undef_method (TYPE_1__*,struct RClass*,char*) ; 
 int /*<<< orphan*/  top_define_method ; 

void
mrb_init_class(mrb_state *mrb)
{
  struct RClass *bob;           /* BasicObject */
  struct RClass *obj;           /* Object */
  struct RClass *mod;           /* Module */
  struct RClass *cls;           /* Class */

  /* boot class hierarchy */
  bob = boot_defclass(mrb, 0);
  obj = boot_defclass(mrb, bob); mrb->object_class = obj;
  mod = boot_defclass(mrb, obj); mrb->module_class = mod;/* obj -> mod */
  cls = boot_defclass(mrb, mod); mrb->class_class = cls; /* obj -> cls */
  /* fix-up loose ends */
  bob->c = obj->c = mod->c = cls->c = cls;
  make_metaclass(mrb, bob);
  make_metaclass(mrb, obj);
  make_metaclass(mrb, mod);
  make_metaclass(mrb, cls);

  /* name basic classes */
  mrb_define_const(mrb, bob, "BasicObject", mrb_obj_value(bob));
  mrb_define_const(mrb, obj, "BasicObject", mrb_obj_value(bob));
  mrb_define_const(mrb, obj, "Object",      mrb_obj_value(obj));
  mrb_define_const(mrb, obj, "Module",      mrb_obj_value(mod));
  mrb_define_const(mrb, obj, "Class",       mrb_obj_value(cls));

  /* name each classes */
  mrb_class_name_class(mrb, NULL, bob, mrb_intern_lit(mrb, "BasicObject"));
  mrb_class_name_class(mrb, NULL, obj, mrb_intern_lit(mrb, "Object")); /* 15.2.1 */
  mrb_class_name_class(mrb, NULL, mod, mrb_intern_lit(mrb, "Module")); /* 15.2.2 */
  mrb_class_name_class(mrb, NULL, cls, mrb_intern_lit(mrb, "Class"));  /* 15.2.3 */

  mrb->proc_class = mrb_define_class(mrb, "Proc", mrb->object_class);  /* 15.2.17 */
  MRB_SET_INSTANCE_TT(mrb->proc_class, MRB_TT_PROC);

  MRB_SET_INSTANCE_TT(cls, MRB_TT_CLASS);
  mrb_define_method(mrb, bob, "initialize",              mrb_bob_init,             MRB_ARGS_NONE());
  mrb_define_method(mrb, bob, "!",                       mrb_bob_not,              MRB_ARGS_NONE());
  mrb_define_method(mrb, bob, "==",                      mrb_obj_equal_m,          MRB_ARGS_REQ(1)); /* 15.3.1.3.1  */
  mrb_define_method(mrb, bob, "!=",                      mrb_obj_not_equal_m,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, bob, "__id__",                  mrb_obj_id_m,             MRB_ARGS_NONE()); /* 15.3.1.3.4  */
  mrb_define_method(mrb, bob, "__send__",                mrb_f_send,               MRB_ARGS_ANY());  /* 15.3.1.3.5  */
  mrb_define_method(mrb, bob, "instance_eval",           mrb_obj_instance_eval,    MRB_ARGS_ANY());  /* 15.3.1.3.18 */

  mrb_define_class_method(mrb, cls, "new",               mrb_class_new_class,      MRB_ARGS_OPT(1));
  mrb_define_method(mrb, cls, "superclass",              mrb_class_superclass,     MRB_ARGS_NONE()); /* 15.2.3.3.4 */
  mrb_define_method(mrb, cls, "new",                     mrb_instance_new,         MRB_ARGS_ANY());  /* 15.2.3.3.3 */
  mrb_define_method(mrb, cls, "initialize",              mrb_class_initialize,     MRB_ARGS_OPT(1)); /* 15.2.3.3.1 */
  mrb_define_method(mrb, cls, "inherited",               mrb_bob_init,             MRB_ARGS_REQ(1));

  MRB_SET_INSTANCE_TT(mod, MRB_TT_MODULE);
  mrb_define_method(mrb, mod, "extend_object",           mrb_mod_extend_object,    MRB_ARGS_REQ(1)); /* 15.2.2.4.25 */
  mrb_define_method(mrb, mod, "extended",                mrb_bob_init,             MRB_ARGS_REQ(1)); /* 15.2.2.4.26 */
  mrb_define_method(mrb, mod, "prepended",               mrb_bob_init,             MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mod, "prepend_features",        mrb_mod_prepend_features, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mod, "include?",                mrb_mod_include_p,        MRB_ARGS_REQ(1)); /* 15.2.2.4.28 */
  mrb_define_method(mrb, mod, "append_features",         mrb_mod_append_features,  MRB_ARGS_REQ(1)); /* 15.2.2.4.10 */
  mrb_define_method(mrb, mod, "class_eval",              mrb_mod_module_eval,      MRB_ARGS_ANY());  /* 15.2.2.4.15 */
  mrb_define_method(mrb, mod, "included",                mrb_bob_init,             MRB_ARGS_REQ(1)); /* 15.2.2.4.29 */
  mrb_define_method(mrb, mod, "initialize",              mrb_mod_initialize,       MRB_ARGS_NONE()); /* 15.2.2.4.31 */
  mrb_define_method(mrb, mod, "module_eval",             mrb_mod_module_eval,      MRB_ARGS_ANY());  /* 15.2.2.4.35 */
  mrb_define_method(mrb, mod, "module_function",         mrb_mod_module_function,  MRB_ARGS_ANY());
  mrb_define_method(mrb, mod, "private",                 mrb_mod_dummy_visibility, MRB_ARGS_ANY());  /* 15.2.2.4.36 */
  mrb_define_method(mrb, mod, "protected",               mrb_mod_dummy_visibility, MRB_ARGS_ANY());  /* 15.2.2.4.37 */
  mrb_define_method(mrb, mod, "public",                  mrb_mod_dummy_visibility, MRB_ARGS_ANY());  /* 15.2.2.4.38 */
  mrb_define_method(mrb, mod, "attr_reader",             mrb_mod_attr_reader,      MRB_ARGS_ANY());  /* 15.2.2.4.13 */
  mrb_define_method(mrb, mod, "attr_writer",             mrb_mod_attr_writer,      MRB_ARGS_ANY());  /* 15.2.2.4.14 */
  mrb_define_method(mrb, mod, "to_s",                    mrb_mod_to_s,             MRB_ARGS_NONE());
  mrb_define_method(mrb, mod, "inspect",                 mrb_mod_to_s,             MRB_ARGS_NONE());
  mrb_define_method(mrb, mod, "alias_method",            mrb_mod_alias,            MRB_ARGS_ANY());  /* 15.2.2.4.8 */
  mrb_define_method(mrb, mod, "ancestors",               mrb_mod_ancestors,        MRB_ARGS_NONE()); /* 15.2.2.4.9 */
  mrb_define_method(mrb, mod, "undef_method",            mrb_mod_undef,            MRB_ARGS_ANY());  /* 15.2.2.4.41 */
  mrb_define_method(mrb, mod, "const_defined?",          mrb_mod_const_defined,    MRB_ARGS_ARG(1,1)); /* 15.2.2.4.20 */
  mrb_define_method(mrb, mod, "const_get",               mrb_mod_const_get,        MRB_ARGS_REQ(1)); /* 15.2.2.4.21 */
  mrb_define_method(mrb, mod, "const_set",               mrb_mod_const_set,        MRB_ARGS_REQ(2)); /* 15.2.2.4.23 */
  mrb_define_method(mrb, mod, "remove_const",            mrb_mod_remove_const,     MRB_ARGS_REQ(1)); /* 15.2.2.4.40 */
  mrb_define_method(mrb, mod, "const_missing",           mrb_mod_const_missing,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mod, "method_defined?",         mrb_mod_method_defined,   MRB_ARGS_REQ(1)); /* 15.2.2.4.34 */
  mrb_define_method(mrb, mod, "define_method",           mod_define_method,        MRB_ARGS_ARG(1,1));
  mrb_define_method(mrb, mod, "===",                     mrb_mod_eqq,              MRB_ARGS_REQ(1));

  mrb_undef_method(mrb, cls, "append_features");
  mrb_undef_method(mrb, cls, "extend_object");

  mrb->top_self = (struct RObject*)mrb_obj_alloc(mrb, MRB_TT_OBJECT, mrb->object_class);
  mrb_define_singleton_method(mrb, mrb->top_self, "inspect", inspect_main, MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, mrb->top_self, "to_s", inspect_main, MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, mrb->top_self, "define_method", top_define_method, MRB_ARGS_ARG(1,1));
}