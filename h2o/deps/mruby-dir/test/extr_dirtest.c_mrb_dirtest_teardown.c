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
struct dirent {char const* d_name; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  E_RUNTIME_ERROR ; 
 int chdir (char const*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_cv_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_cstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ *,char const*) ; 
 char* mrb_str_to_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_true_value () ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int rmdir (char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

mrb_value
mrb_dirtest_teardown(mrb_state *mrb, mrb_value klass)
{
  mrb_value d, sandbox;
  DIR *dirp;
  struct dirent *dp;
  const char *path;

  /* cleanup sandbox */
  sandbox = mrb_cv_get(mrb, klass, mrb_intern_cstr(mrb, "sandbox"));
  path = mrb_str_to_cstr(mrb, sandbox);

  dirp = opendir(path);
  while ((dp = readdir(dirp)) != NULL) {
    if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
      continue;
    if (rmdir(dp->d_name) == -1) {
      mrb_raisef(mrb, E_RUNTIME_ERROR, "rmdir(%S) failed", mrb_str_new_cstr(mrb, dp->d_name));
    }
  }
  closedir(dirp);

  /* back to original pwd */
  d = mrb_cv_get(mrb, klass, mrb_intern_cstr(mrb, "pwd"));
  path = mrb_str_to_cstr(mrb, d);
  if (chdir(path) == -1) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "chdir(%S) failed", d);
  }

  /* remove sandbox directory */
  sandbox = mrb_cv_get(mrb, klass, mrb_intern_cstr(mrb, "sandbox"));
  path = mrb_str_to_cstr(mrb, sandbox);
  if (rmdir(path) == -1) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "rmdir(%S) failed", sandbox);
  }

  return mrb_true_value();
}