#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_int ;
typedef  int mrb_bool ;
struct TYPE_2__ {int* beg; int* end; int num_regs; } ;
typedef  TYPE_1__ OnigRegion ;
typedef  int /*<<< orphan*/  OnigRegex ;

/* Variables and functions */
 scalar_t__ DATA_PTR (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Data_Get_Struct (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_TYPE_ERROR ; 
 int /*<<< orphan*/  ONIG_REGEXP_P (int /*<<< orphan*/ ) ; 
 int RARRAY_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ RSTRING_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_onig_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_ary_new_from_values (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_ary_pop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,...) ; 
 int mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  mrb_gv_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_obj_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_onig_regexp_type ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_str_new_lit (int /*<<< orphan*/ *,char*) ; 
 char* mrb_str_to_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_string_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_string_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int onig_match_common (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  str_substr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int utf8len (char*,char*) ; 

__attribute__((used)) static mrb_value
string_split(mrb_state* mrb, mrb_value self) {
  mrb_value pattern = mrb_nil_value(); mrb_int limit = 0;
  int argc = mrb_get_args(mrb, "|oi", &pattern, &limit);
  mrb_value result, tmp;
  mrb_bool lim_p = !(argc == 2 && 0 < limit);

  if(mrb_nil_p(pattern)) { // check $; global variable
    pattern = mrb_gv_get(mrb, mrb_intern_lit(mrb, "$;"));
    if (mrb_nil_p(pattern)) {
      pattern = mrb_str_new_lit(mrb, " ");
    } else if (!mrb_string_p(pattern) && !ONIG_REGEXP_P(pattern)) {
      mrb_raise(mrb, E_TYPE_ERROR, "value of $; must be String or Regexp");
    }
    if (argc == 0) { argc = 1; }
  }

  if (!ONIG_REGEXP_P(pattern)) {
    if(!mrb_nil_p(pattern)) { pattern = mrb_string_type(mrb, pattern); }
    if(mrb_string_p(pattern) && RSTRING_LEN(pattern) == 0) {
      /* Special case - split into chars */
      pattern = mrb_funcall(mrb, mrb_obj_value(mrb_class_get(mrb, "OnigRegexp")), "new", 1, pattern);
    } else {
      return mrb_funcall(mrb, self, "string_split", argc, pattern, mrb_fixnum_value(limit));
    }
  }

  if(RSTRING_LEN(self) == 0) { return mrb_ary_new(mrb); }
  if(limit == 1) { return mrb_ary_new_from_values(mrb, 1, &self); }

  result = mrb_ary_new(mrb);

  OnigRegex reg;
  Data_Get_Struct(mrb, pattern, &mrb_onig_regexp_type, reg);
  mrb_value const match_value = create_onig_region(mrb, self, pattern);
  OnigRegion* const match = (OnigRegion*)DATA_PTR(match_value);
  char *ptr = mrb_str_to_cstr(mrb, self);
  mrb_int len = RSTRING_LEN(self);
  mrb_int start = 0, beg = 0, end = 0;
  mrb_int idx = 0, i = 0;
  mrb_int last_null = 0;

  if (argc == 2) { i = 1; }
  while ((end = onig_match_common(mrb, reg, match_value, self, start)) >= 0) {
    if (start == end && match->beg[0] == match->end[0]) {
      if (!ptr) {
        mrb_ary_push(mrb, result, mrb_str_new_lit(mrb, ""));
        break;
      }
      else if (last_null == 1) {
        mrb_ary_push(mrb, result, str_substr(mrb, self, beg, utf8len(ptr+beg, ptr+len)));
        beg = start;
      }
      else {
        if (start == len)
          start++;
        else
          start += utf8len(ptr+start, ptr+len);
        last_null = 1;
        continue;
      }
    }
    else {
      mrb_ary_push(mrb, result, str_substr(mrb, self, beg, end-beg));
      beg = start = match->end[0];
    }
    last_null = 0;

    for (idx=1; idx < match->num_regs; idx++) {
      if (match->beg[idx] == -1) continue;
      if (match->beg[idx] == match->end[idx])
        tmp = mrb_str_new_lit(mrb, "");
      else
        tmp = str_substr(mrb, self, match->beg[idx], match->end[idx]-match->beg[idx]);
      mrb_ary_push(mrb, result, tmp);
    }
    if (!lim_p && limit <= ++i) break;
  }

  if (RSTRING_LEN(self) > 0 && (!lim_p || RSTRING_LEN(self) > beg || limit < 0)) {
    if (RSTRING_LEN(self) == beg)
      tmp = mrb_str_new_lit(mrb, "");
    else
      tmp = str_substr(mrb, self, beg, RSTRING_LEN(self)-beg);
    mrb_ary_push(mrb, result, tmp);
  }
  if (lim_p && limit == 0) {
    while ((len = RARRAY_LEN(result)) > 0 &&
        (tmp = mrb_ary_ref(mrb, result, len-1), RSTRING_LEN(tmp) == 0))
      mrb_ary_pop(mrb, result);
  }

  return result;
}