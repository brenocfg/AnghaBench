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
 int /*<<< orphan*/  mrb_fixnum_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_format (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_gc_arena_restore (int /*<<< orphan*/ *,int) ; 
 int mrb_gc_arena_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_locale_free (char const*) ; 
 char* mrb_locale_from_utf8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_str_to_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int symlink (char const*,char const*) ; 

__attribute__((used)) static mrb_value
mrb_file_s_symlink(mrb_state *mrb, mrb_value klass)
{
#if defined(_WIN32) || defined(_WIN64)
  mrb_raise(mrb, E_NOTIMP_ERROR, "symlink is not supported on this platform");
#else
  mrb_value from, to;
  const char *src, *dst;
  int ai = mrb_gc_arena_save(mrb);

  mrb_get_args(mrb, "SS", &from, &to);
  src = mrb_locale_from_utf8(mrb_str_to_cstr(mrb, from), -1);
  dst = mrb_locale_from_utf8(mrb_str_to_cstr(mrb, to), -1);

  if (symlink(src, dst) == -1) {
    mrb_locale_free(src);
    mrb_locale_free(dst);
    mrb_sys_fail(mrb, mrb_str_to_cstr(mrb, mrb_format(mrb, "(%S, %S)", from, to)));
  }
  mrb_locale_free(src);
  mrb_locale_free(dst);
  mrb_gc_arena_restore(mrb, ai);
#endif
  return mrb_fixnum_value(0);
}