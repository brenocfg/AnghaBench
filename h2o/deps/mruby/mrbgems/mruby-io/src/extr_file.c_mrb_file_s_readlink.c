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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMP_ERROR ; 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_gc_arena_restore (int /*<<< orphan*/ *,int) ; 
 int mrb_gc_arena_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  mrb_locale_free (char*) ; 
 char* mrb_locale_from_utf8 (char*,int) ; 
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mrb_realloc (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  mrb_str_new (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 
 char* mrb_utf8_from_locale (char*,int) ; 
 int readlink (char*,char*,size_t) ; 

__attribute__((used)) static mrb_value
mrb_file_s_readlink(mrb_state *mrb, mrb_value klass) {
#if defined(_WIN32) || defined(_WIN64)
  mrb_raise(mrb, E_NOTIMP_ERROR, "readlink is not supported on this platform");
  return mrb_nil_value(); // unreachable
#else
  char *path, *buf, *tmp;
  size_t bufsize = 100;
  ssize_t rc;
  mrb_value ret;
  int ai = mrb_gc_arena_save(mrb);

  mrb_get_args(mrb, "z", &path);
  tmp = mrb_locale_from_utf8(path, -1);

  buf = (char *)mrb_malloc(mrb, bufsize);
  while ((rc = readlink(tmp, buf, bufsize)) == (ssize_t)bufsize && rc != -1) {
    bufsize *= 2;
    buf = (char *)mrb_realloc(mrb, buf, bufsize);
  }
  mrb_locale_free(tmp);
  if (rc == -1) {
    mrb_free(mrb, buf);
    mrb_sys_fail(mrb, path);
  }
  tmp = mrb_utf8_from_locale(buf, -1);
  ret = mrb_str_new(mrb, tmp, rc);
  mrb_locale_free(tmp);
  mrb_free(mrb, buf);

  mrb_gc_arena_restore(mrb, ai);
  return ret;
#endif
}