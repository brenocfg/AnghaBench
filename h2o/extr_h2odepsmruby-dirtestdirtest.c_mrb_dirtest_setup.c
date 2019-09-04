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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  E_RUNTIME_ERROR ; 
 char* P_tmpdir ; 
 int chdir (char*) ; 
 int /*<<< orphan*/ * getcwd (char*,int) ; 
 int mkdir (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mkdtemp (char*) ; 
 int /*<<< orphan*/  mrb_cv_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_cstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  mrb_true_value () ; 
 int /*<<< orphan*/  rmdir (char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

mrb_value
mrb_dirtest_setup(mrb_state *mrb, mrb_value klass)
{
  mrb_value s;
  char buf[1024];
  const char *aname = "a";
  const char *bname = "b";

  /* save current working directory */
  if (getcwd(buf, sizeof(buf)) == NULL) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "getcwd() failed");
  }
  mrb_cv_set(mrb, klass, mrb_intern_cstr(mrb, "pwd"), mrb_str_new_cstr(mrb, buf));

  /* create sandbox */
#if defined(_WIN32) || defined(_WIN64)
  snprintf(buf, sizeof(buf), "%s\\mruby-dir-test.XXXXXX", _getcwd(NULL,0));
  if ((mktemp(buf) == NULL) || mkdir(buf) != 0) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "mkdtemp(%S) failed", mrb_str_new_cstr(mrb, buf));
  }
#else
  snprintf(buf, sizeof(buf), "%s/mruby-dir-test.XXXXXX", P_tmpdir);
  if (mkdtemp(buf) == NULL) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "mkdtemp(%S) failed", mrb_str_new_cstr(mrb, buf));
  }
#endif
  s = mrb_str_new_cstr(mrb, buf);
  mrb_cv_set(mrb, klass, mrb_intern_cstr(mrb, "sandbox"), s);

  /* go to sandbox */
  if (chdir(buf) == -1) {
    rmdir(buf);
    mrb_raisef(mrb, E_RUNTIME_ERROR, "chdir(%S) failed", s);
  }
  
  /* make some directories in the sandbox */
#if defined(_WIN32) || defined(_WIN64)
  if (mkdir(aname) == -1) {
#else
  if (mkdir(aname, 0) == -1) {
#endif
    chdir("..");
    rmdir(buf);
    mrb_raisef(mrb, E_RUNTIME_ERROR, "mkdir(%S) failed", mrb_str_new_cstr(mrb, aname));
  }
#if defined(_WIN32) || defined(_WIN64)
  if (mkdir(bname) == -1) {
#else
  if (mkdir(bname, 0) == -1) {
#endif
    rmdir(aname);
    chdir("..");
    rmdir(buf);
    mrb_raisef(mrb, E_RUNTIME_ERROR, "mkdir(%S) failed", mrb_str_new_cstr(mrb, bname));
  }

  return mrb_true_value();
}