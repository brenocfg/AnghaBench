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

/* Variables and functions */
 int /*<<< orphan*/  E_RUNTIME_ERROR ; 
 int /*<<< orphan*/  MRB_TT_STRING ; 
 int /*<<< orphan*/  mrb_convert_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 char* mrb_string_value_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ setenv (char const*,char const*,int) ; 
 scalar_t__ unsetenv (char const*) ; 

__attribute__((used)) static mrb_value
mrb_env_aset(mrb_state *mrb, mrb_value self)
{
  mrb_value name, value;
  const char *cname, *cvalue;

  mrb_get_args(mrb, "So", &name, &value);
  cname = mrb_string_value_cstr(mrb, &name);

  if (mrb_nil_p(value)) {
    if (unsetenv(cname) != 0) {
      mrb_raise(mrb, E_RUNTIME_ERROR, "can't delete environment variable");
    }
  } else {
    mrb_convert_type(mrb, value, MRB_TT_STRING, "String", "to_str");
    cvalue = mrb_string_value_cstr(mrb, &value);
    if (setenv(cname, cvalue, 1) != 0) {
      mrb_raise(mrb, E_RUNTIME_ERROR, "can't change environment variable");
    }
  }
  return value;
}