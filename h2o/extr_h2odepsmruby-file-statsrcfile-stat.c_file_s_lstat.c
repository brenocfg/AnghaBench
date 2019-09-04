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
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  Data_Wrap_Struct (int /*<<< orphan*/ *,struct RClass*,int /*<<< orphan*/ *,struct stat*) ; 
 int LSTAT (char*,struct stat*) ; 
 int /*<<< orphan*/  MRB_TT_STRING ; 
 int /*<<< orphan*/  mrb_check_convert_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 struct RClass* mrb_class_get_under (int /*<<< orphan*/ *,struct RClass*,char*) ; 
 struct RClass* mrb_class_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_convert_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (int /*<<< orphan*/ ) ; 
 struct stat* mrb_stat_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_stat_type ; 
 char* mrb_str_to_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static mrb_value
file_s_lstat(mrb_state *mrb, mrb_value klass)
{
  struct RClass *file_class;
  struct RClass *stat_class;
  struct stat st, *ptr;
  mrb_value fname, tmp;
  char *path;

  mrb_get_args(mrb, "o", &fname);

  tmp = mrb_check_convert_type(mrb, fname, MRB_TT_STRING, "String", "to_path");
  if (mrb_nil_p(tmp)) {
    tmp = mrb_convert_type(mrb, fname, MRB_TT_STRING, "String", "to_str");
  }
  path = mrb_str_to_cstr(mrb, tmp);
  if (LSTAT(path, &st) == -1) {
    mrb_sys_fail(mrb, path);
  }

  file_class = mrb_class_ptr(klass);
  stat_class = mrb_class_get_under(mrb, file_class, "Stat");
  ptr = mrb_stat_alloc(mrb);
  *ptr = st;

  return mrb_obj_value(Data_Wrap_Struct(mrb, stat_class, &mrb_stat_type, ptr));
}