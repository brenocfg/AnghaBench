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

/* Variables and functions */
 scalar_t__ ISLOWER (char) ; 
 scalar_t__ ISUPPER (char) ; 
 int RSTRING_LEN (int /*<<< orphan*/ ) ; 
 char* RSTRING_PTR (int /*<<< orphan*/ ) ; 
 char TOLOWER (char) ; 
 char TOUPPER (char) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_str_modify (int /*<<< orphan*/ *,struct RString*) ; 
 struct RString* mrb_str_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_str_swapcase_bang(mrb_state *mrb, mrb_value str)
{
  char *p, *pend;
  int modify = 0;
  struct RString *s = mrb_str_ptr(str);

  mrb_str_modify(mrb, s);
  p = RSTRING_PTR(str);
  pend = p + RSTRING_LEN(str);
  while (p < pend) {
    if (ISUPPER(*p)) {
      *p = TOLOWER(*p);
      modify = 1;
    }
    else if (ISLOWER(*p)) {
      *p = TOUPPER(*p);
      modify = 1;
    }
    p++;
  }

  if (modify) return str;
  return mrb_nil_value();
}