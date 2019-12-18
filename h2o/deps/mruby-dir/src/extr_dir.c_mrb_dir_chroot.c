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
 int /*<<< orphan*/  E_NOTIMP_ERROR ; 
 int chroot (char*) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 char* mrb_str_to_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 

mrb_value
mrb_dir_chroot(mrb_state *mrb, mrb_value self)
{
  #if defined(_WIN32) || defined(_WIN64) || defined(__android__)
  mrb_raise(mrb, E_NOTIMP_ERROR, "chroot() unreliable on Win platforms");
  return mrb_fixnum_value(0);
  #else
  mrb_value spath;
  char *path;
  int res;

  mrb_get_args(mrb, "S", &spath);
  path = mrb_str_to_cstr(mrb, spath);
  res = chroot(path);
  if (res == -1) {
    mrb_sys_fail(mrb, path);
  }

  return mrb_fixnum_value(res);
  #endif
}