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
struct TYPE_5__ {int /*<<< orphan*/  object_class; struct RClass* hash_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_ARGS_ANY () ; 
 int /*<<< orphan*/  MRB_ARGS_NONE () ; 
 int /*<<< orphan*/  MRB_ARGS_OPT (int) ; 
 int /*<<< orphan*/  MRB_ARGS_REQ (int) ; 
 int /*<<< orphan*/  MRB_SET_INSTANCE_TT (struct RClass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRB_TT_HASH ; 
 struct RClass* mrb_define_class (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_hash_aget ; 
 int /*<<< orphan*/  mrb_hash_aset ; 
 int /*<<< orphan*/  mrb_hash_clear ; 
 int /*<<< orphan*/  mrb_hash_default ; 
 int /*<<< orphan*/  mrb_hash_default_proc ; 
 int /*<<< orphan*/  mrb_hash_delete ; 
 int /*<<< orphan*/  mrb_hash_empty_m ; 
 int /*<<< orphan*/  mrb_hash_has_key ; 
 int /*<<< orphan*/  mrb_hash_has_value ; 
 int /*<<< orphan*/  mrb_hash_init ; 
 int /*<<< orphan*/  mrb_hash_init_copy ; 
 int /*<<< orphan*/  mrb_hash_keys ; 
 int /*<<< orphan*/  mrb_hash_rehash ; 
 int /*<<< orphan*/  mrb_hash_set_default ; 
 int /*<<< orphan*/  mrb_hash_set_default_proc ; 
 int /*<<< orphan*/  mrb_hash_shift ; 
 int /*<<< orphan*/  mrb_hash_size_m ; 
 int /*<<< orphan*/  mrb_hash_values ; 

void
mrb_init_hash(mrb_state *mrb)
{
  struct RClass *h;

  mrb->hash_class = h = mrb_define_class(mrb, "Hash", mrb->object_class);              /* 15.2.13 */
  MRB_SET_INSTANCE_TT(h, MRB_TT_HASH);

  mrb_define_method(mrb, h, "initialize_copy", mrb_hash_init_copy,   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, h, "[]",              mrb_hash_aget,        MRB_ARGS_REQ(1)); /* 15.2.13.4.2  */
  mrb_define_method(mrb, h, "[]=",             mrb_hash_aset,        MRB_ARGS_REQ(2)); /* 15.2.13.4.3  */
  mrb_define_method(mrb, h, "clear",           mrb_hash_clear,       MRB_ARGS_NONE()); /* 15.2.13.4.4  */
  mrb_define_method(mrb, h, "default",         mrb_hash_default,     MRB_ARGS_ANY());  /* 15.2.13.4.5  */
  mrb_define_method(mrb, h, "default=",        mrb_hash_set_default, MRB_ARGS_REQ(1)); /* 15.2.13.4.6  */
  mrb_define_method(mrb, h, "default_proc",    mrb_hash_default_proc,MRB_ARGS_NONE()); /* 15.2.13.4.7  */
  mrb_define_method(mrb, h, "default_proc=",   mrb_hash_set_default_proc,MRB_ARGS_REQ(1)); /* 15.2.13.4.7  */
  mrb_define_method(mrb, h, "__delete",        mrb_hash_delete,      MRB_ARGS_REQ(1)); /* core of 15.2.13.4.8  */
  mrb_define_method(mrb, h, "empty?",          mrb_hash_empty_m,     MRB_ARGS_NONE()); /* 15.2.13.4.12 */
  mrb_define_method(mrb, h, "has_key?",        mrb_hash_has_key,     MRB_ARGS_REQ(1)); /* 15.2.13.4.13 */
  mrb_define_method(mrb, h, "has_value?",      mrb_hash_has_value,   MRB_ARGS_REQ(1)); /* 15.2.13.4.14 */
  mrb_define_method(mrb, h, "include?",        mrb_hash_has_key,     MRB_ARGS_REQ(1)); /* 15.2.13.4.15 */
  mrb_define_method(mrb, h, "initialize",      mrb_hash_init,        MRB_ARGS_OPT(1)); /* 15.2.13.4.16 */
  mrb_define_method(mrb, h, "key?",            mrb_hash_has_key,     MRB_ARGS_REQ(1)); /* 15.2.13.4.18 */
  mrb_define_method(mrb, h, "keys",            mrb_hash_keys,        MRB_ARGS_NONE()); /* 15.2.13.4.19 */
  mrb_define_method(mrb, h, "length",          mrb_hash_size_m,      MRB_ARGS_NONE()); /* 15.2.13.4.20 */
  mrb_define_method(mrb, h, "member?",         mrb_hash_has_key,     MRB_ARGS_REQ(1)); /* 15.2.13.4.21 */
  mrb_define_method(mrb, h, "shift",           mrb_hash_shift,       MRB_ARGS_NONE()); /* 15.2.13.4.24 */
  mrb_define_method(mrb, h, "size",            mrb_hash_size_m,      MRB_ARGS_NONE()); /* 15.2.13.4.25 */
  mrb_define_method(mrb, h, "store",           mrb_hash_aset,        MRB_ARGS_REQ(2)); /* 15.2.13.4.26 */
  mrb_define_method(mrb, h, "value?",          mrb_hash_has_value,   MRB_ARGS_REQ(1)); /* 15.2.13.4.27 */
  mrb_define_method(mrb, h, "values",          mrb_hash_values,      MRB_ARGS_NONE()); /* 15.2.13.4.28 */
  mrb_define_method(mrb, h, "rehash",          mrb_hash_rehash,      MRB_ARGS_NONE());
}