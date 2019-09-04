#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_4__ {int* beg; int* end; int const num_regs; } ;
typedef  int /*<<< orphan*/  OnigUChar ;
typedef  TYPE_1__ OnigRegion ;
typedef  int /*<<< orphan*/  OnigRegex ;

/* Variables and functions */
 int /*<<< orphan*/  E_INDEX_ERROR ; 
 int /*<<< orphan*/  E_REGEXP_ERROR ; 
 int RSTRING_LEN (int /*<<< orphan*/ ) ; 
 char const* RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int /*<<< orphan*/  mrb_assert (int) ; 
 int /*<<< orphan*/  mrb_hash_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_hash_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_cat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  mrb_str_cat_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_substr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mrb_str_to_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mrb_string_p (int /*<<< orphan*/ ) ; 
 int onig_name_to_backref_number (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int /*<<< orphan*/  str_substr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
append_replace_str(mrb_state* mrb, mrb_value result, mrb_value replace,
                   mrb_value src, OnigRegex reg, OnigRegion* match)
{
  if (mrb_hash_p(replace)) {
    mrb_value v = mrb_hash_get(mrb, replace, mrb_str_substr(mrb, src, match->beg[0], match->end[0] - match->beg[0]));
    v = mrb_str_to_str(mrb, v);
    mrb_str_cat_str(mrb, result, v);
    return;
  }

  mrb_assert(mrb_string_p(replace));
  char const* ch;
  char const* const end = RSTRING_PTR(replace) + RSTRING_LEN(replace);
  for(ch = RSTRING_PTR(replace); ch < end; ++ch) {
    if (*ch != '\\' || (ch + 1) >= end) {
      mrb_str_cat(mrb, result, ch, 1);
      continue;
    }

    switch(*(++ch)) { // skip back slash and get next char
      case 'k': { // group name
        if ((ch + 2) >= end || ch[1] != '<') { goto replace_expr_error; }
        char const* name_beg = ch += 2;
        while (*ch != '>') { if(++ch == end) { goto replace_expr_error; } }
        mrb_assert(ch < end);
        mrb_assert(*ch == '>');
        int const idx = onig_name_to_backref_number(
            reg, (OnigUChar const*)name_beg, (OnigUChar const*)ch, match);
        if (idx < 0) {
          mrb_raisef(mrb, E_INDEX_ERROR, "undefined group name reference: %S",
                     str_substr(mrb, replace, name_beg - RSTRING_PTR(replace), ch - name_beg));
        }
        mrb_str_cat(mrb, result, RSTRING_PTR(src) + match->beg[idx], match->end[idx] - match->beg[idx]);
      } break;

      case '\\': // escaped back slash
        mrb_str_cat(mrb, result, ch, 1);
        break;

      default:
        if (isdigit(*ch)) { // group number 0-9
          int const idx = *ch - '0';
          if (idx < match->num_regs) {
            mrb_str_cat(mrb, result, RSTRING_PTR(src) + match->beg[idx], match->end[idx] - match->beg[idx]);
          }
        } else {
          char const str[] = { '\\', *ch };
          mrb_str_cat(mrb, result, str, 2);
        }
        break;
    }
  }

  if(ch == end) { return; }

replace_expr_error:
  mrb_raisef(mrb, E_REGEXP_ERROR, "invalid replace expression: %S", replace);
}