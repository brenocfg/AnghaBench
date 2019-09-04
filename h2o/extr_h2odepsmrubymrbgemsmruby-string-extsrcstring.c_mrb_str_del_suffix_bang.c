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
struct RString {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_FROZEN_P (struct RString*) ; 
 struct RString* RSTRING (int /*<<< orphan*/ ) ; 
 scalar_t__ RSTR_FSHARED_P (struct RString*) ; 
 scalar_t__ RSTR_LEN (struct RString*) ; 
 char* RSTR_PTR (struct RString*) ; 
 int /*<<< orphan*/  RSTR_SET_LEN (struct RString*,scalar_t__) ; 
 scalar_t__ RSTR_SHARED_P (struct RString*) ; 
 scalar_t__ memcmp (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,char**,scalar_t__*) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_str_modify (int /*<<< orphan*/ *,struct RString*) ; 

__attribute__((used)) static mrb_value
mrb_str_del_suffix_bang(mrb_state *mrb, mrb_value self)
{
  mrb_int plen, slen;
  char *ptr, *s;
  struct RString *str = RSTRING(self);

  mrb_get_args(mrb, "s", &ptr, &plen);
  slen = RSTR_LEN(str);
  if (plen > slen) return mrb_nil_value();
  s = RSTR_PTR(str);
  if (memcmp(s+slen-plen, ptr, plen) != 0) return mrb_nil_value();
  if (!MRB_FROZEN_P(str) && (RSTR_SHARED_P(str) || RSTR_FSHARED_P(str))) {
    /* no need to modify string */
  }
  else {
    mrb_str_modify(mrb, str);
  }
  RSTR_SET_LEN(str, slen-plen);
  return self;
}