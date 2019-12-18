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
 int /*<<< orphan*/ * GETCWD (char*,int) ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_utf8_free (char*) ; 
 char* mrb_utf8_from_locale (char*,int) ; 

mrb_value
mrb_file__getwd(mrb_state *mrb, mrb_value klass)
{
  mrb_value path;
  char buf[MAXPATHLEN], *utf8;

  if (GETCWD(buf, MAXPATHLEN) == NULL) {
    mrb_sys_fail(mrb, "getcwd(2)");
  }
  utf8 = mrb_utf8_from_locale(buf, -1);
  path = mrb_str_new_cstr(mrb, utf8);
  mrb_utf8_free(utf8);
  return path;
}