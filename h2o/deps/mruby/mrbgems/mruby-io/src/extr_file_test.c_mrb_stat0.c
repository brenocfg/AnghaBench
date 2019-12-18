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
struct stat {int dummy; } ;
struct mrb_io {scalar_t__ fd; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  E_IO_ERROR ; 
 int LSTAT (char*,struct stat*) ; 
 int fstat (scalar_t__,struct stat*) ; 
 int /*<<< orphan*/  mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_get_datatype (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_io_type ; 
 int /*<<< orphan*/  mrb_locale_free (char*) ; 
 char* mrb_locale_from_utf8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_obj_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_str_to_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_test (int /*<<< orphan*/ ) ; 
 int stat (char*,struct stat*) ; 

__attribute__((used)) static int
mrb_stat0(mrb_state *mrb, mrb_value obj, struct stat *st, int do_lstat)
{
  mrb_value tmp;
  mrb_value io_klass, str_klass;

  io_klass  = mrb_obj_value(mrb_class_get(mrb, "IO"));
  str_klass = mrb_obj_value(mrb_class_get(mrb, "String"));

  tmp = mrb_funcall(mrb, obj, "is_a?", 1, io_klass);
  if (mrb_test(tmp)) {
    struct mrb_io *fptr;
    fptr = (struct mrb_io *)mrb_get_datatype(mrb, obj, &mrb_io_type);

    if (fptr && fptr->fd >= 0) {
      return fstat(fptr->fd, st);
    }

    mrb_raise(mrb, E_IO_ERROR, "closed stream");
    return -1;
  }

  tmp = mrb_funcall(mrb, obj, "is_a?", 1, str_klass);
  if (mrb_test(tmp)) {
    char *path = mrb_locale_from_utf8(mrb_str_to_cstr(mrb, obj), -1);
    int ret;
    if (do_lstat) {
      ret = LSTAT(path, st);
    } else {
      ret = stat(path, st);
    }
    mrb_locale_free(path);
    return ret;
  }

  return -1;
}