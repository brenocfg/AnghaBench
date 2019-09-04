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
 int mkdir (char*,int) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int*) ; 
 char* mrb_str_to_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 

mrb_value
mrb_dir_mkdir(mrb_state *mrb, mrb_value klass)
{
  mrb_int mode;
  mrb_value spath;
  char *path;

  mode = 0777;
  mrb_get_args(mrb, "S|i", &spath, &mode);
  path = mrb_str_to_cstr(mrb, spath);
#ifndef _WIN32
  if (mkdir(path, mode) == -1) {
#else
  if (mkdir(path) == -1) {
#endif
    mrb_sys_fail(mrb, path);
  }
  return mrb_fixnum_value(0);
}