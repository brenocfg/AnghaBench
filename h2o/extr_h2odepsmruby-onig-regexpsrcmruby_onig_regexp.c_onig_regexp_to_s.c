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
typedef  int /*<<< orphan*/  OnigUChar ;
typedef  int /*<<< orphan*/  OnigRegex ;

/* Variables and functions */
 int /*<<< orphan*/  Data_Get_Struct (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ONIG_ENCODING_UTF8 ; 
 int /*<<< orphan*/  ONIG_OPTION_DEFAULT ; 
 int ONIG_OPTION_EXTEND ; 
 int ONIG_OPTION_IGNORECASE ; 
 int ONIG_OPTION_MULTILINE ; 
 int /*<<< orphan*/  OnigDefaultSyntax ; 
 long RSTRING_LEN (int /*<<< orphan*/ ) ; 
 char* RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_iv_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_onig_regexp_type ; 
 int /*<<< orphan*/  mrb_str_cat_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_str_new_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  onig_free (int /*<<< orphan*/ ) ; 
 int onig_get_options (int /*<<< orphan*/ ) ; 
 int onig_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__* option_to_str (char*,int) ; 
 int /*<<< orphan*/  regexp_expr_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,long) ; 
 scalar_t__ strchr (char const*,char) ; 

__attribute__((used)) static mrb_value
onig_regexp_to_s(mrb_state *mrb, mrb_value self) {
  int options;
  const int embeddable = ONIG_OPTION_MULTILINE|ONIG_OPTION_IGNORECASE|ONIG_OPTION_EXTEND;
  long len;
  const char* ptr;
  mrb_value str = mrb_str_new_lit(mrb, "(?");
  char optbuf[5];

  OnigRegex reg;
  Data_Get_Struct(mrb, self, &mrb_onig_regexp_type, reg);
  options = onig_get_options(reg);
  mrb_value src = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@source"));
  ptr = RSTRING_PTR(src);
  len = RSTRING_LEN(src);

 again:
  if (len >= 4 && ptr[0] == '(' && ptr[1] == '?') {
    int err = 1;
    ptr += 2;
    if ((len -= 2) > 0) {
      do {
        if(strchr(ptr, 'i')) { options |= ONIG_OPTION_IGNORECASE; }
        if(strchr(ptr, 'x')) { options |= ONIG_OPTION_EXTEND; }
        if(strchr(ptr, 'm')) { options |= ONIG_OPTION_MULTILINE; }
        ++ptr;
      } while (--len > 0);
    }
    if (len > 1 && *ptr == '-') {
      ++ptr;
      --len;
      do {
        if(strchr(ptr, 'i')) { options &= ~ONIG_OPTION_IGNORECASE; }
        if(strchr(ptr, 'x')) { options &= ~ONIG_OPTION_EXTEND; }
        if(strchr(ptr, 'm')) { options &= ~ONIG_OPTION_MULTILINE; }
        ++ptr;
      } while (--len > 0);
    }
    if (*ptr == ')') {
      --len;
      ++ptr;
      goto again;
    }
    if (*ptr == ':' && ptr[len-1] == ')') {
      OnigRegex rp;
      ++ptr;
      len -= 2;
      err = onig_new(&rp, (OnigUChar*)ptr, (OnigUChar*)ptr + len, ONIG_OPTION_DEFAULT,
                     ONIG_ENCODING_UTF8, OnigDefaultSyntax, NULL);
      onig_free(rp);
    }
    if (err) {
      options = onig_get_options(reg);
      ptr = RSTRING_PTR(src);
      len = RSTRING_LEN(src);
    }
  }

  if (*option_to_str(optbuf, options)) mrb_str_cat_cstr(mrb, str, optbuf);

  if ((options & embeddable) != embeddable) {
    optbuf[0] = '-';
    option_to_str(optbuf + 1, ~options);
    mrb_str_cat_cstr(mrb, str, optbuf);
  }

  mrb_str_cat_cstr(mrb, str, ":");
  regexp_expr_str(mrb, str, ptr, len);
  mrb_str_cat_cstr(mrb, str, ")");
  return str;
}