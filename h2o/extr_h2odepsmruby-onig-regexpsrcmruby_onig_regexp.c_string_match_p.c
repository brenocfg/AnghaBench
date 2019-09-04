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
typedef  scalar_t__ mrb_int ;
typedef  int OnigUChar ;
typedef  int /*<<< orphan*/  OnigRegex ;

/* Variables and functions */
 scalar_t__ ONIG_MISMATCH ; 
 int RSTRING_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_bool_value (int) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_onig_regexp_type ; 
 int /*<<< orphan*/  mrb_string_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ onig_search (int /*<<< orphan*/ ,int const*,int const*,int const*,int const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
string_match_p(mrb_state *mrb, mrb_value self) {
  mrb_value str = self;
  mrb_int pos = 0;
  OnigRegex reg;
  OnigUChar const* str_ptr;

  mrb_get_args(mrb, "d|i", &reg, &mrb_onig_regexp_type, &pos);
  if (pos < 0 || (pos > 0 && pos >= RSTRING_LEN(str))) {
    return mrb_nil_value();
  }

  if (mrb_nil_p(str)) {
    return mrb_nil_value();
  }
  str = mrb_string_type(mrb, str);

  str_ptr = (OnigUChar const*)RSTRING_PTR(str);
  return mrb_bool_value(onig_search(
      reg, str_ptr, str_ptr + RSTRING_LEN(str),
      str_ptr + pos, str_ptr + RSTRING_LEN(str), NULL, 0) != ONIG_MISMATCH);
}