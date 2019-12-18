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
struct TYPE_5__ {struct RClass* fixnum_class; struct RClass* string_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int MRB_ARGS_NONE () ; 
 int MRB_ARGS_OPT (int) ; 
 int MRB_ARGS_REQ (int) ; 
 int MRB_ARGS_REST () ; 
 int /*<<< orphan*/  mrb_define_alias (TYPE_1__*,struct RClass*,char*,char*) ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_fixnum_chr ; 
 int /*<<< orphan*/  mrb_str_byteslice ; 
 int /*<<< orphan*/  mrb_str_chr ; 
 int /*<<< orphan*/  mrb_str_concat_m ; 
 int /*<<< orphan*/  mrb_str_count ; 
 int /*<<< orphan*/  mrb_str_del_prefix ; 
 int /*<<< orphan*/  mrb_str_del_prefix_bang ; 
 int /*<<< orphan*/  mrb_str_del_suffix ; 
 int /*<<< orphan*/  mrb_str_del_suffix_bang ; 
 int /*<<< orphan*/  mrb_str_delete ; 
 int /*<<< orphan*/  mrb_str_delete_bang ; 
 int /*<<< orphan*/  mrb_str_dump ; 
 int /*<<< orphan*/  mrb_str_end_with ; 
 int /*<<< orphan*/  mrb_str_getbyte ; 
 int /*<<< orphan*/  mrb_str_hex ; 
 int /*<<< orphan*/  mrb_str_lines ; 
 int /*<<< orphan*/  mrb_str_oct ; 
 int /*<<< orphan*/  mrb_str_ord ; 
 int /*<<< orphan*/  mrb_str_setbyte ; 
 int /*<<< orphan*/  mrb_str_squeeze ; 
 int /*<<< orphan*/  mrb_str_squeeze_bang ; 
 int /*<<< orphan*/  mrb_str_start_with ; 
 int /*<<< orphan*/  mrb_str_succ ; 
 int /*<<< orphan*/  mrb_str_succ_bang ; 
 int /*<<< orphan*/  mrb_str_swapcase ; 
 int /*<<< orphan*/  mrb_str_swapcase_bang ; 
 int /*<<< orphan*/  mrb_str_tr ; 
 int /*<<< orphan*/  mrb_str_tr_bang ; 
 int /*<<< orphan*/  mrb_str_tr_s ; 
 int /*<<< orphan*/  mrb_str_tr_s_bang ; 

void
mrb_mruby_string_ext_gem_init(mrb_state* mrb)
{
  struct RClass * s = mrb->string_class;

  mrb_define_method(mrb, s, "dump",            mrb_str_dump,            MRB_ARGS_NONE());
  mrb_define_method(mrb, s, "getbyte",         mrb_str_getbyte,         MRB_ARGS_REQ(1));
  mrb_define_method(mrb, s, "setbyte",         mrb_str_setbyte,         MRB_ARGS_REQ(2));
  mrb_define_method(mrb, s, "byteslice",       mrb_str_byteslice,       MRB_ARGS_REQ(1)|MRB_ARGS_OPT(1));
  mrb_define_method(mrb, s, "swapcase!",       mrb_str_swapcase_bang,   MRB_ARGS_NONE());
  mrb_define_method(mrb, s, "swapcase",        mrb_str_swapcase,        MRB_ARGS_NONE());
  mrb_define_method(mrb, s, "concat",          mrb_str_concat_m,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, s, "<<",              mrb_str_concat_m,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, s, "count",           mrb_str_count,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, s, "tr",              mrb_str_tr,              MRB_ARGS_REQ(2));
  mrb_define_method(mrb, s, "tr!",             mrb_str_tr_bang,         MRB_ARGS_REQ(2));
  mrb_define_method(mrb, s, "tr_s",            mrb_str_tr_s,            MRB_ARGS_REQ(2));
  mrb_define_method(mrb, s, "tr_s!",           mrb_str_tr_s_bang,       MRB_ARGS_REQ(2));
  mrb_define_method(mrb, s, "squeeze",         mrb_str_squeeze,         MRB_ARGS_OPT(1));
  mrb_define_method(mrb, s, "squeeze!",        mrb_str_squeeze_bang,    MRB_ARGS_OPT(1));
  mrb_define_method(mrb, s, "delete",          mrb_str_delete,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, s, "delete!",         mrb_str_delete_bang,     MRB_ARGS_REQ(1));
  mrb_define_method(mrb, s, "start_with?",     mrb_str_start_with,      MRB_ARGS_REST());
  mrb_define_method(mrb, s, "end_with?",       mrb_str_end_with,        MRB_ARGS_REST());
  mrb_define_method(mrb, s, "hex",             mrb_str_hex,             MRB_ARGS_NONE());
  mrb_define_method(mrb, s, "oct",             mrb_str_oct,             MRB_ARGS_NONE());
  mrb_define_method(mrb, s, "chr",             mrb_str_chr,             MRB_ARGS_NONE());
  mrb_define_method(mrb, s, "succ",            mrb_str_succ,            MRB_ARGS_NONE());
  mrb_define_method(mrb, s, "succ!",           mrb_str_succ_bang,       MRB_ARGS_NONE());
  mrb_define_alias(mrb,  s, "next",            "succ");
  mrb_define_alias(mrb,  s, "next!",           "succ!");
  mrb_define_method(mrb, s, "ord",             mrb_str_ord,             MRB_ARGS_NONE());
  mrb_define_method(mrb, s, "delete_prefix!",  mrb_str_del_prefix_bang, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, s, "delete_prefix",   mrb_str_del_prefix,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, s, "delete_suffix!",  mrb_str_del_suffix_bang, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, s, "delete_suffix",   mrb_str_del_suffix,      MRB_ARGS_REQ(1));

  mrb_define_method(mrb, s, "__lines",         mrb_str_lines,           MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb->fixnum_class, "chr", mrb_fixnum_chr, MRB_ARGS_NONE());
}