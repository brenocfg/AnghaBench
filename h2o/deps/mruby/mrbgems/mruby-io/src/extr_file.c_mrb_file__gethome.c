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
struct passwd {char* pw_dir; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 char* getenv (char*) ; 
 struct passwd* getpwnam (char const*) ; 
 int /*<<< orphan*/  mrb_file_is_absolute_path (char*) ; 
 scalar_t__ mrb_get_argc (int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_locale_free (char*) ; 
 char* mrb_locale_from_utf8 (char*,int) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ *,char*) ; 
 char* mrb_str_to_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_file__gethome(mrb_state *mrb, mrb_value klass)
{
  mrb_int argc;
  char *home;
  mrb_value path;

#ifndef _WIN32
  mrb_value username;

  argc = mrb_get_args(mrb, "|S", &username);
  if (argc == 0) {
    home = getenv("HOME");
    if (home == NULL) {
      return mrb_nil_value();
    }
    if (!mrb_file_is_absolute_path(home)) {
      mrb_raise(mrb, E_ARGUMENT_ERROR, "non-absolute home");
    }
  } else {
    const char *cuser = mrb_str_to_cstr(mrb, username);
    struct passwd *pwd = getpwnam(cuser);
    if (pwd == NULL) {
      return mrb_nil_value();
    }
    home = pwd->pw_dir;
    if (!mrb_file_is_absolute_path(home)) {
      mrb_raisef(mrb, E_ARGUMENT_ERROR, "non-absolute home of ~%S", username);
    }
  }
  home = mrb_locale_from_utf8(home, -1);
  path = mrb_str_new_cstr(mrb, home);
  mrb_locale_free(home);
  return path;
#else
  argc = mrb_get_argc(mrb);
  if (argc == 0) {
    home = getenv("USERPROFILE");
    if (home == NULL) {
      return mrb_nil_value();
    }
    if (!mrb_file_is_absolute_path(home)) {
      mrb_raise(mrb, E_ARGUMENT_ERROR, "non-absolute home");
    }
  } else {
    return mrb_nil_value();
  }
  home = mrb_locale_from_utf8(home, -1);
  path = mrb_str_new_cstr(mrb, home);
  mrb_locale_free(home);
  return path;
#endif
}