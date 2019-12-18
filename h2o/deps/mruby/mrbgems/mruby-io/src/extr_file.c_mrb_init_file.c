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
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_ALT_SEPARATOR ; 
 int /*<<< orphan*/  FILE_SEPARATOR ; 
 int /*<<< orphan*/  LOCK_EX ; 
 int /*<<< orphan*/  LOCK_NB ; 
 int /*<<< orphan*/  LOCK_SH ; 
 int /*<<< orphan*/  LOCK_UN ; 
 int MRB_ARGS_ANY () ; 
 int MRB_ARGS_NONE () ; 
 int MRB_ARGS_OPT (int) ; 
 int MRB_ARGS_REQ (int) ; 
 int MRB_ARGS_REST () ; 
 int /*<<< orphan*/  MRB_SET_INSTANCE_TT (struct RClass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRB_TT_DATA ; 
 int /*<<< orphan*/  NULL_FILE ; 
 int /*<<< orphan*/  PATH_SEPARATOR ; 
 struct RClass* mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 struct RClass* mrb_define_class (int /*<<< orphan*/ *,char*,struct RClass*) ; 
 int /*<<< orphan*/  mrb_define_class_method (int /*<<< orphan*/ *,struct RClass*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_define_const (int /*<<< orphan*/ *,struct RClass*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_method (int /*<<< orphan*/ *,struct RClass*,char*,int /*<<< orphan*/ ,int) ; 
 struct RClass* mrb_define_module_under (int /*<<< orphan*/ *,struct RClass*,char*) ; 
 int /*<<< orphan*/  mrb_file__gethome ; 
 int /*<<< orphan*/  mrb_file__getwd ; 
 int /*<<< orphan*/  mrb_file_basename ; 
 int /*<<< orphan*/  mrb_file_dirname ; 
 int /*<<< orphan*/  mrb_file_flock ; 
 int /*<<< orphan*/  mrb_file_mtime ; 
 int /*<<< orphan*/  mrb_file_realpath ; 
 int /*<<< orphan*/  mrb_file_s_chmod ; 
 int /*<<< orphan*/  mrb_file_s_readlink ; 
 int /*<<< orphan*/  mrb_file_s_rename ; 
 int /*<<< orphan*/  mrb_file_s_symlink ; 
 int /*<<< orphan*/  mrb_file_s_umask ; 
 int /*<<< orphan*/  mrb_file_s_unlink ; 
 int /*<<< orphan*/  mrb_fixnum_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
mrb_init_file(mrb_state *mrb)
{
  struct RClass *io, *file, *cnst;

  io   = mrb_class_get(mrb, "IO");
  file = mrb_define_class(mrb, "File", io);
  MRB_SET_INSTANCE_TT(file, MRB_TT_DATA);
  mrb_define_class_method(mrb, file, "umask",  mrb_file_s_umask, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, file, "delete", mrb_file_s_unlink, MRB_ARGS_ANY());
  mrb_define_class_method(mrb, file, "unlink", mrb_file_s_unlink, MRB_ARGS_ANY());
  mrb_define_class_method(mrb, file, "rename", mrb_file_s_rename, MRB_ARGS_REQ(2));
  mrb_define_class_method(mrb, file, "symlink", mrb_file_s_symlink, MRB_ARGS_REQ(2));
  mrb_define_class_method(mrb, file, "chmod", mrb_file_s_chmod, MRB_ARGS_REQ(1) | MRB_ARGS_REST());
  mrb_define_class_method(mrb, file, "readlink", mrb_file_s_readlink, MRB_ARGS_REQ(1));

  mrb_define_class_method(mrb, file, "dirname",   mrb_file_dirname,    MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, file, "basename",  mrb_file_basename,   MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, file, "realpath",  mrb_file_realpath,   MRB_ARGS_REQ(1)|MRB_ARGS_OPT(1));
  mrb_define_class_method(mrb, file, "_getwd",    mrb_file__getwd,     MRB_ARGS_NONE());
  mrb_define_class_method(mrb, file, "_gethome",  mrb_file__gethome,   MRB_ARGS_OPT(1));

  mrb_define_method(mrb, file, "flock", mrb_file_flock, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, file, "mtime", mrb_file_mtime, MRB_ARGS_NONE());

  cnst = mrb_define_module_under(mrb, file, "Constants");
  mrb_define_const(mrb, cnst, "LOCK_SH", mrb_fixnum_value(LOCK_SH));
  mrb_define_const(mrb, cnst, "LOCK_EX", mrb_fixnum_value(LOCK_EX));
  mrb_define_const(mrb, cnst, "LOCK_UN", mrb_fixnum_value(LOCK_UN));
  mrb_define_const(mrb, cnst, "LOCK_NB", mrb_fixnum_value(LOCK_NB));
  mrb_define_const(mrb, cnst, "SEPARATOR", mrb_str_new_cstr(mrb, FILE_SEPARATOR));
  mrb_define_const(mrb, cnst, "PATH_SEPARATOR", mrb_str_new_cstr(mrb, PATH_SEPARATOR));
#if defined(_WIN32) || defined(_WIN64)
  mrb_define_const(mrb, cnst, "ALT_SEPARATOR", mrb_str_new_cstr(mrb, FILE_ALT_SEPARATOR));
#else
  mrb_define_const(mrb, cnst, "ALT_SEPARATOR", mrb_nil_value());
#endif
  mrb_define_const(mrb, cnst, "NULL", mrb_str_new_cstr(mrb, NULL_FILE));

}