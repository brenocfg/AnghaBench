#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct RObject {int dummy; } ;
struct RClass {int dummy; } ;
struct TYPE_10__ {struct RClass* string_class; int /*<<< orphan*/  object_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int MRB_ARGS_BLOCK () ; 
 int MRB_ARGS_NONE () ; 
 int MRB_ARGS_OPT (int) ; 
 int MRB_ARGS_REQ (int) ; 
 int /*<<< orphan*/  MRB_SET_INSTANCE_TT (struct RClass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRB_TT_DATA ; 
 int /*<<< orphan*/  ONIG_OPTION_ASCII_RANGE ; 
 int /*<<< orphan*/  ONIG_OPTION_CAPTURE_GROUP ; 
 int /*<<< orphan*/  ONIG_OPTION_DONT_CAPTURE_GROUP ; 
 int /*<<< orphan*/  ONIG_OPTION_EXTEND ; 
 int /*<<< orphan*/  ONIG_OPTION_FIND_LONGEST ; 
 int /*<<< orphan*/  ONIG_OPTION_FIND_NOT_EMPTY ; 
 int /*<<< orphan*/  ONIG_OPTION_IGNORECASE ; 
 int /*<<< orphan*/  ONIG_OPTION_MULTILINE ; 
 int /*<<< orphan*/  ONIG_OPTION_NEGATE_SINGLELINE ; 
 int /*<<< orphan*/  ONIG_OPTION_NEWLINE_CRLF ; 
 int /*<<< orphan*/  ONIG_OPTION_NOTBOL ; 
 int /*<<< orphan*/  ONIG_OPTION_NOTBOS ; 
 int /*<<< orphan*/  ONIG_OPTION_NOTEOL ; 
 int /*<<< orphan*/  ONIG_OPTION_NOTEOS ; 
 int /*<<< orphan*/  ONIG_OPTION_POSIX_BRACKET_ALL_RANGE ; 
 int /*<<< orphan*/  ONIG_OPTION_POSIX_REGION ; 
 int /*<<< orphan*/  ONIG_OPTION_SINGLELINE ; 
 int /*<<< orphan*/  ONIG_OPTION_WORD_BOUND_ALL_RANGE ; 
 int /*<<< orphan*/  match_data_begin ; 
 int /*<<< orphan*/  match_data_captures ; 
 int /*<<< orphan*/  match_data_copy ; 
 int /*<<< orphan*/  match_data_end ; 
 int /*<<< orphan*/  match_data_index ; 
 int /*<<< orphan*/  match_data_length ; 
 int /*<<< orphan*/  match_data_offset ; 
 int /*<<< orphan*/  match_data_post_match ; 
 int /*<<< orphan*/  match_data_pre_match ; 
 int /*<<< orphan*/  match_data_regexp ; 
 int /*<<< orphan*/  match_data_string ; 
 int /*<<< orphan*/  match_data_to_a ; 
 int /*<<< orphan*/  match_data_to_s ; 
 struct RClass* mrb_define_class (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_const (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mrb_define_module_function (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mrb_obj_iv_set (TYPE_1__*,struct RObject*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_true_value () ; 
 int /*<<< orphan*/  mrb_undef_class_method (TYPE_1__*,struct RClass*,char*) ; 
 int /*<<< orphan*/ * onig_regexp_casefold_p ; 
 int /*<<< orphan*/  onig_regexp_clear_global_variables ; 
 int /*<<< orphan*/  onig_regexp_does_set_global_variables ; 
 int /*<<< orphan*/ * onig_regexp_equal ; 
 int /*<<< orphan*/  onig_regexp_escape ; 
 int /*<<< orphan*/ * onig_regexp_initialize ; 
 int /*<<< orphan*/ * onig_regexp_inspect ; 
 int /*<<< orphan*/ * onig_regexp_match ; 
 int /*<<< orphan*/ * onig_regexp_match_p ; 
 int /*<<< orphan*/ * onig_regexp_options ; 
 int /*<<< orphan*/  onig_regexp_set_set_global_variables ; 
 int /*<<< orphan*/ * onig_regexp_to_s ; 
 int /*<<< orphan*/  onig_regexp_version ; 
 int /*<<< orphan*/  string_gsub ; 
 int /*<<< orphan*/  string_match_p ; 
 int /*<<< orphan*/  string_scan ; 
 int /*<<< orphan*/  string_split ; 
 int /*<<< orphan*/  string_sub ; 

void
mrb_mruby_onig_regexp_gem_init(mrb_state* mrb) {
  struct RClass *clazz;

  clazz = mrb_define_class(mrb, "OnigRegexp", mrb->object_class);
  MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);

  // enable global variables setting in onig_match_common by default
  mrb_obj_iv_set(mrb, (struct RObject*)clazz, mrb_intern_lit(mrb, "@set_global_variables"), mrb_true_value());

  mrb_define_const(mrb, clazz, "IGNORECASE", mrb_fixnum_value(ONIG_OPTION_IGNORECASE));
  mrb_define_const(mrb, clazz, "EXTENDED", mrb_fixnum_value(ONIG_OPTION_EXTEND));
  mrb_define_const(mrb, clazz, "MULTILINE", mrb_fixnum_value(ONIG_OPTION_MULTILINE));
  mrb_define_const(mrb, clazz, "SINGLELINE", mrb_fixnum_value(ONIG_OPTION_SINGLELINE));
  mrb_define_const(mrb, clazz, "FIND_LONGEST", mrb_fixnum_value(ONIG_OPTION_FIND_LONGEST));
  mrb_define_const(mrb, clazz, "FIND_NOT_EMPTY", mrb_fixnum_value(ONIG_OPTION_FIND_NOT_EMPTY));
  mrb_define_const(mrb, clazz, "NEGATE_SINGLELINE", mrb_fixnum_value(ONIG_OPTION_NEGATE_SINGLELINE));
  mrb_define_const(mrb, clazz, "DONT_CAPTURE_GROUP", mrb_fixnum_value(ONIG_OPTION_DONT_CAPTURE_GROUP));
  mrb_define_const(mrb, clazz, "CAPTURE_GROUP", mrb_fixnum_value(ONIG_OPTION_CAPTURE_GROUP));
  mrb_define_const(mrb, clazz, "NOTBOL", mrb_fixnum_value(ONIG_OPTION_NOTBOL));
  mrb_define_const(mrb, clazz, "NOTEOL", mrb_fixnum_value(ONIG_OPTION_NOTEOL));
#ifdef ONIG_OPTION_POSIX_REGION
  mrb_define_const(mrb, clazz, "POSIX_REGION", mrb_fixnum_value(ONIG_OPTION_POSIX_REGION));
#endif
#ifdef ONIG_OPTION_ASCII_RANGE
  mrb_define_const(mrb, clazz, "ASCII_RANGE", mrb_fixnum_value(ONIG_OPTION_ASCII_RANGE));
#endif
#ifdef ONIG_OPTION_POSIX_BRACKET_ALL_RANGE
  mrb_define_const(mrb, clazz, "POSIX_BRACKET_ALL_RANGE", mrb_fixnum_value(ONIG_OPTION_POSIX_BRACKET_ALL_RANGE));
#endif
#ifdef ONIG_OPTION_WORD_BOUND_ALL_RANGE
  mrb_define_const(mrb, clazz, "WORD_BOUND_ALL_RANGE", mrb_fixnum_value(ONIG_OPTION_WORD_BOUND_ALL_RANGE));
#endif
#ifdef ONIG_OPTION_NEWLINE_CRLF
  mrb_define_const(mrb, clazz, "NEWLINE_CRLF", mrb_fixnum_value(ONIG_OPTION_NEWLINE_CRLF));
#endif
#ifdef ONIG_OPTION_NOTBOS
  mrb_define_const(mrb, clazz, "NOTBOS", mrb_fixnum_value(ONIG_OPTION_NOTBOS));
#endif
#ifdef ONIG_OPTION_NOTEOS
  mrb_define_const(mrb, clazz, "NOTEOS", mrb_fixnum_value(ONIG_OPTION_NOTEOS));
#endif

  mrb_define_method(mrb, clazz, "initialize", onig_regexp_initialize, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(2));
  mrb_define_method(mrb, clazz, "==", onig_regexp_equal, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, clazz, "match", onig_regexp_match, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
  mrb_define_method(mrb, clazz, "match?", onig_regexp_match_p, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
  mrb_define_method(mrb, clazz, "casefold?", onig_regexp_casefold_p, MRB_ARGS_NONE());

  mrb_define_method(mrb, clazz, "options", onig_regexp_options, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "inspect", onig_regexp_inspect, MRB_ARGS_NONE());
  mrb_define_method(mrb, clazz, "to_s", onig_regexp_to_s, MRB_ARGS_NONE());

  mrb_define_module_function(mrb, clazz, "escape", onig_regexp_escape, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, clazz, "quote", onig_regexp_escape, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, clazz, "version", onig_regexp_version, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, clazz, "set_global_variables?", onig_regexp_does_set_global_variables, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, clazz, "set_global_variables=", onig_regexp_set_set_global_variables, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, clazz, "clear_global_variables", onig_regexp_clear_global_variables, MRB_ARGS_NONE());

  struct RClass* match_data = mrb_define_class(mrb, "OnigMatchData", mrb->object_class);
  MRB_SET_INSTANCE_TT(clazz, MRB_TT_DATA);
  mrb_undef_class_method(mrb, match_data, "new");

  // mrb_define_method(mrb, match_data, "==", &match_data_eq);
  mrb_define_method(mrb, match_data, "[]", &match_data_index, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, match_data, "begin", &match_data_begin, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, match_data, "captures", &match_data_captures, MRB_ARGS_NONE());
  mrb_define_method(mrb, match_data, "end", &match_data_end, MRB_ARGS_REQ(1));
  // mrb_define_method(mrb, match_data, "eql?", &match_data_eq);
  // mrb_define_method(mrb, match_data, "hash", &match_data_hash);
  mrb_define_method(mrb, match_data, "initialize_copy", &match_data_copy, MRB_ARGS_REQ(1));
  // mrb_define_method(mrb, match_data, "inspect", &match_data_inspect);
  mrb_define_method(mrb, match_data, "length", &match_data_length, MRB_ARGS_NONE());
  // mrb_define_method(mrb, match_data, "names", &match_data_names);
  mrb_define_method(mrb, match_data, "offset", &match_data_offset, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, match_data, "post_match", &match_data_post_match, MRB_ARGS_NONE());
  mrb_define_method(mrb, match_data, "pre_match", &match_data_pre_match, MRB_ARGS_NONE());
  mrb_define_method(mrb, match_data, "regexp", &match_data_regexp, MRB_ARGS_NONE());
  mrb_define_method(mrb, match_data, "size", &match_data_length, MRB_ARGS_NONE());
  mrb_define_method(mrb, match_data, "string", &match_data_string, MRB_ARGS_NONE());
  mrb_define_method(mrb, match_data, "to_a", &match_data_to_a, MRB_ARGS_NONE());
  mrb_define_method(mrb, match_data, "to_s", &match_data_to_s, MRB_ARGS_NONE());
  // mrb_define_method(mrb, match_data, "values_at", &match_data_values_at);

  mrb_define_method(mrb, mrb->string_class, "onig_regexp_gsub", &string_gsub, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, mrb->string_class, "onig_regexp_sub", &string_sub, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, mrb->string_class, "onig_regexp_split", &string_split, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb->string_class, "onig_regexp_scan", &string_scan, MRB_ARGS_REQ(1) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, mrb->string_class, "onig_regexp_match?", &string_match_p, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
}