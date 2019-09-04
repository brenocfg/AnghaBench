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
typedef  int mrb_int ;

/* Variables and functions */
 int RSTRING_LEN (int /*<<< orphan*/ ) ; 
 char* RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_name_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_cv_name_str(mrb_state *mrb, mrb_value str)
{
  const char *s = RSTRING_PTR(str);
  mrb_int len = RSTRING_LEN(str);

  if (len < 3 || !(s[0] == '@' && s[1] == '@')) {
    mrb_name_error(mrb, mrb_intern_str(mrb, str), "'%S' is not allowed as a class variable name", str);
  }
}