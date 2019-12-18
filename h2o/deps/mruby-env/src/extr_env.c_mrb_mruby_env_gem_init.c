#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct RObject {int dummy; } ;
struct RClass {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  object_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_ARGS_NONE () ; 
 int /*<<< orphan*/  MRB_ARGS_REQ (int) ; 
 int /*<<< orphan*/  MRB_TT_OBJECT ; 
 int /*<<< orphan*/  mrb_class_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mrb_define_global_const (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_singleton_method (TYPE_1__*,struct RObject*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_env_aget ; 
 int /*<<< orphan*/  mrb_env_aset ; 
 int /*<<< orphan*/  mrb_env_has_key ; 
 int /*<<< orphan*/  mrb_env_inspect ; 
 int /*<<< orphan*/  mrb_env_keys ; 
 int /*<<< orphan*/  mrb_env_size ; 
 int /*<<< orphan*/  mrb_env_to_a ; 
 int /*<<< orphan*/  mrb_env_to_hash ; 
 int /*<<< orphan*/  mrb_env_to_s ; 
 int /*<<< orphan*/  mrb_env_values ; 
 int /*<<< orphan*/  mrb_include_module (TYPE_1__*,struct RClass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_module_get (TYPE_1__*,char*) ; 
 scalar_t__ mrb_obj_alloc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RObject*) ; 

void
mrb_mruby_env_gem_init(mrb_state *mrb)
{
  struct RObject *e;

  e = (struct RObject*) mrb_obj_alloc(mrb, MRB_TT_OBJECT, mrb->object_class);
#if defined(MRUBY_RELEASE_NO) && MRUBY_RELEASE_NO >= 10000
  mrb_include_module(mrb, (struct RClass*)e, mrb_module_get(mrb, "Enumerable"));
#else
  mrb_include_module(mrb, (struct RClass*)e, mrb_class_get(mrb, "Enumerable"));
#endif

  mrb_define_singleton_method(mrb, e,"[]",       mrb_env_aget,       MRB_ARGS_REQ(1));
  mrb_define_singleton_method(mrb, e,"[]=",      mrb_env_aset,       MRB_ARGS_REQ(2));
  mrb_define_singleton_method(mrb, e,"has_key?", mrb_env_has_key,    MRB_ARGS_REQ(1));
  mrb_define_singleton_method(mrb, e,"inspect",  mrb_env_inspect,    MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, e,"keys",     mrb_env_keys,       MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, e,"size",     mrb_env_size,       MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, e,"store",    mrb_env_aset,       MRB_ARGS_REQ(2));
  mrb_define_singleton_method(mrb, e,"to_a",     mrb_env_to_a,       MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, e,"to_hash",  mrb_env_to_hash,    MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, e,"to_s",     mrb_env_to_s,       MRB_ARGS_NONE());
  mrb_define_singleton_method(mrb, e,"values",   mrb_env_values,     MRB_ARGS_NONE());

  mrb_define_global_const(mrb, "ENV", mrb_obj_value(e));
}