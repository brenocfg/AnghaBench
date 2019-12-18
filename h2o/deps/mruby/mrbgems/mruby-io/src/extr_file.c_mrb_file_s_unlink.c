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
typedef  size_t mrb_int ;

/* Variables and functions */
 scalar_t__ UNLINK (char*) ; 
 int /*<<< orphan*/  mrb_ensure_string_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (size_t) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  mrb_locale_free (char*) ; 
 char* mrb_locale_from_utf8 (char const*,int) ; 
 char* mrb_string_value_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static mrb_value
mrb_file_s_unlink(mrb_state *mrb, mrb_value obj)
{
  mrb_value *argv;
  mrb_value pathv;
  mrb_int argc, i;
  char *path;

  mrb_get_args(mrb, "*", &argv, &argc);
  for (i = 0; i < argc; i++) {
    const char *utf8_path;
    pathv = mrb_ensure_string_type(mrb, argv[i]);
    utf8_path = mrb_string_value_cstr(mrb, &pathv);
    path = mrb_locale_from_utf8(utf8_path, -1);
    if (UNLINK(path) < 0) {
      mrb_locale_free(path);
      mrb_sys_fail(mrb, utf8_path);
    }
    mrb_locale_free(path);
  }
  return mrb_fixnum_value(argc);
}