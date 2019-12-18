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
 char* getenv (char const*) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ *,char const*) ; 
 char* mrb_string_value_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

mrb_value
mrb_env_aget(mrb_state *mrb, mrb_value self)
{
  mrb_value key;
  const char *cname, *cvalue;

  mrb_get_args(mrb, "S", &key);
  cname = mrb_string_value_cstr(mrb, &key);
  cvalue = getenv(cname);
  if (cvalue != NULL) {
    return mrb_str_new_cstr(mrb, cvalue);
  } else {
    return mrb_nil_value();
  }
}