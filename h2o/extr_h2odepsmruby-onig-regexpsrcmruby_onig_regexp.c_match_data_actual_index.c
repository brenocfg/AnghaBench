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
typedef  int /*<<< orphan*/  const mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_int ;
typedef  int /*<<< orphan*/  OnigUChar ;
typedef  int /*<<< orphan*/  OnigRegion ;
typedef  int /*<<< orphan*/  OnigRegex ;

/* Variables and functions */
 scalar_t__ DATA_PTR (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * DATA_TYPE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  E_INDEX_ERROR ; 
 int FALSE ; 
 int /*<<< orphan*/  mrb_assert (int) ; 
 int mrb_fixnum (int /*<<< orphan*/  const) ; 
 scalar_t__ mrb_fixnum_p (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  const mrb_iv_get (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_p (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  mrb_onig_regexp_type ; 
 int /*<<< orphan*/  mrb_onig_region_type ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const) ; 
 scalar_t__ mrb_string_p (int /*<<< orphan*/  const) ; 
 char* mrb_string_value_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 char* mrb_sym2name_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mrb_symbol (int /*<<< orphan*/  const) ; 
 scalar_t__ mrb_symbol_p (int /*<<< orphan*/  const) ; 
 int onig_name_to_backref_number (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 

__attribute__((used)) static mrb_int
match_data_actual_index(mrb_state* mrb, mrb_value self, mrb_value idx_value) {
  if(mrb_fixnum_p(idx_value)) { return mrb_fixnum(idx_value); }

  char const* name = NULL;
  char const* name_end = NULL;
  if(mrb_symbol_p(idx_value)) {
    mrb_int sym_len;
    name = mrb_sym2name_len(mrb, mrb_symbol(idx_value), &sym_len);
    name_end = name + sym_len;
  } else if(mrb_string_p(idx_value)) {
    name = mrb_string_value_ptr(mrb, idx_value);
    name_end = name + strlen(name);
  } else { mrb_assert(FALSE); }
  mrb_assert(name && name_end);

  mrb_value const regexp = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "regexp"));
  mrb_assert(!mrb_nil_p(regexp));
  mrb_assert(DATA_TYPE(regexp) == &mrb_onig_regexp_type);
  mrb_assert(DATA_TYPE(self) == &mrb_onig_region_type);
  int const idx = onig_name_to_backref_number(
      (OnigRegex)DATA_PTR(regexp), (OnigUChar const*)name, (OnigUChar const*)name_end,
      (OnigRegion*)DATA_PTR(self));
  if (idx < 0) {
    mrb_raisef(mrb, E_INDEX_ERROR, "undefined group name reference: %S", idx_value);
  }
  return idx;
}