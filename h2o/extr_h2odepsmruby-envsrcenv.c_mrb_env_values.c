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
 int /*<<< orphan*/ ** environ ; 
 int /*<<< orphan*/  mrb_ary_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new (int /*<<< orphan*/ *,char*,int) ; 
 char* strchr (int /*<<< orphan*/ *,char) ; 
 int strlen (char*) ; 

mrb_value
mrb_env_values(mrb_state *mrb, mrb_value self)
{
  int i;
  mrb_value ary;

  ary = mrb_ary_new(mrb);
  for (i = 0; environ[i] != NULL; i++) {
    char *str = strchr(environ[i], '=');
    if (str) {
      int len;
      str++;
      len = strlen(str);
      mrb_ary_push(mrb, ary, mrb_str_new(mrb, str, len));
    }
  }

  return ary;
}