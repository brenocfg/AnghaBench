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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  OnigRegex ;

/* Variables and functions */
 int /*<<< orphan*/  Data_Get_Struct (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ONIG_ENCODING_ASCII ; 
 int /*<<< orphan*/  RSTRING_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_iv_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_onig_regexp_type ; 
 int /*<<< orphan*/  mrb_str_cat_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_str_cat_lit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_str_new_lit (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ onig_get_encoding (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onig_get_options (int /*<<< orphan*/ ) ; 
 scalar_t__* option_to_str (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regexp_expr_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
onig_regexp_inspect(mrb_state *mrb, mrb_value self) {
  OnigRegex reg;
  Data_Get_Struct(mrb, self, &mrb_onig_regexp_type, reg);
  mrb_value str = mrb_str_new_lit(mrb, "/");
  mrb_value src = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@source"));
  regexp_expr_str(mrb, str, (const char *)RSTRING_PTR(src), RSTRING_LEN(src));
  mrb_str_cat_lit(mrb, str, "/");
  char opts[4];
  if (*option_to_str(opts, onig_get_options(reg))) {
    mrb_str_cat_cstr(mrb, str, opts);
  }
  if (onig_get_encoding(reg) == ONIG_ENCODING_ASCII) {
    mrb_str_cat_lit(mrb, str, "n");
  }
  return str;
}