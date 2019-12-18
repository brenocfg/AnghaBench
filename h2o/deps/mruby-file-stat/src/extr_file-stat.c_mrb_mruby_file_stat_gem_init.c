#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct RClass {int dummy; } ;
struct TYPE_7__ {struct RClass* object_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_ARGS_NONE () ; 
 int /*<<< orphan*/  MRB_ARGS_REQ (int) ; 
 int /*<<< orphan*/  MRB_SET_INSTANCE_TT (struct RClass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRB_TT_DATA ; 
 int /*<<< orphan*/  file_s_lstat ; 
 int /*<<< orphan*/  io_stat ; 
 struct RClass* mrb_define_class (TYPE_1__*,char*,struct RClass*) ; 
 int /*<<< orphan*/  mrb_define_class_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct RClass* mrb_define_class_under (TYPE_1__*,struct RClass*,char*,struct RClass*) ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat_atime ; 
 int /*<<< orphan*/  stat_birthtime ; 
 int /*<<< orphan*/  stat_blksize ; 
 int /*<<< orphan*/  stat_blockdev_p ; 
 int /*<<< orphan*/  stat_blocks ; 
 int /*<<< orphan*/  stat_chardev_p ; 
 int /*<<< orphan*/  stat_ctime ; 
 int /*<<< orphan*/  stat_dev ; 
 int /*<<< orphan*/  stat_dev_major ; 
 int /*<<< orphan*/  stat_dev_minor ; 
 int /*<<< orphan*/  stat_directory_p ; 
 int /*<<< orphan*/  stat_executable_p ; 
 int /*<<< orphan*/  stat_executable_real_p ; 
 int /*<<< orphan*/  stat_file_p ; 
 int /*<<< orphan*/  stat_ftype ; 
 int /*<<< orphan*/  stat_gid ; 
 int /*<<< orphan*/  stat_grpowned_p ; 
 int /*<<< orphan*/  stat_initialize ; 
 int /*<<< orphan*/  stat_initialize_copy ; 
 int /*<<< orphan*/  stat_ino ; 
 int /*<<< orphan*/  stat_mode ; 
 int /*<<< orphan*/  stat_mtime ; 
 int /*<<< orphan*/  stat_nlink ; 
 int /*<<< orphan*/  stat_owned_p ; 
 int /*<<< orphan*/  stat_owned_real_p ; 
 int /*<<< orphan*/  stat_pipe_p ; 
 int /*<<< orphan*/  stat_rdev ; 
 int /*<<< orphan*/  stat_rdev_major ; 
 int /*<<< orphan*/  stat_rdev_minor ; 
 int /*<<< orphan*/  stat_readable_p ; 
 int /*<<< orphan*/  stat_readable_real_p ; 
 int /*<<< orphan*/  stat_setgid_p ; 
 int /*<<< orphan*/  stat_setuid_p ; 
 int /*<<< orphan*/  stat_size ; 
 int /*<<< orphan*/  stat_socket_p ; 
 int /*<<< orphan*/  stat_sticky_p ; 
 int /*<<< orphan*/  stat_symlink_p ; 
 int /*<<< orphan*/  stat_uid ; 
 int /*<<< orphan*/  stat_world_readable_p ; 
 int /*<<< orphan*/  stat_world_writable_p ; 
 int /*<<< orphan*/  stat_writable_p ; 
 int /*<<< orphan*/  stat_writable_real_p ; 

void
mrb_mruby_file_stat_gem_init(mrb_state* mrb)
{
  struct RClass *io = mrb_define_class(mrb, "IO", mrb->object_class);
  struct RClass *file = mrb_define_class(mrb, "File", io);
  struct RClass *stat = mrb_define_class_under(mrb, file, "Stat", mrb->object_class);

  MRB_SET_INSTANCE_TT(stat, MRB_TT_DATA);

  mrb_define_method(mrb, io, "stat", io_stat, MRB_ARGS_NONE());

  mrb_define_class_method(mrb, file, "lstat", file_s_lstat, MRB_ARGS_REQ(1));

  mrb_define_method(mrb, stat, "initialize", stat_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, stat, "initialize_copy", stat_initialize_copy, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, stat, "dev", stat_dev, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "dev_major", stat_dev_major, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "dev_minor", stat_dev_minor, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "ino", stat_ino, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "mode", stat_mode, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "nlink", stat_nlink, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "uid", stat_uid, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "gid", stat_gid, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "rdev", stat_rdev, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "rdev_major", stat_rdev_major, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "rdev_minor", stat_rdev_minor, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "atime", stat_atime, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "mtime", stat_mtime, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "ctime", stat_ctime, MRB_ARGS_NONE());
#ifdef HAVE_METHOD_BIRTHTIME
  mrb_define_method(mrb, stat, "birthtime", stat_birthtime, MRB_ARGS_NONE());
#endif
  mrb_define_method(mrb, stat, "size", stat_size, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "blksize", stat_blksize, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "blocks", stat_blocks, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "grpowned?", stat_grpowned_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "readable?", stat_readable_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "readable_real?", stat_readable_real_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "world_readable?", stat_world_readable_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "writable?", stat_writable_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "writable_real?", stat_writable_real_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "world_writable?", stat_world_writable_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "executable?", stat_executable_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "executable_real?", stat_executable_real_p, MRB_ARGS_NONE());

  mrb_define_method(mrb, stat, "symlink?", stat_symlink_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "file?", stat_file_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "directory?", stat_directory_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "chardev?", stat_chardev_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "blockdev?", stat_blockdev_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "pipe?", stat_pipe_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "socket?", stat_socket_p, MRB_ARGS_NONE());

  mrb_define_method(mrb, stat, "setuid?", stat_setuid_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "setgid?", stat_setgid_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "sticky?", stat_sticky_p, MRB_ARGS_NONE());

  mrb_define_method(mrb, stat, "ftype", stat_ftype, MRB_ARGS_NONE());

  mrb_define_method(mrb, stat, "owned?", stat_owned_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, stat, "owned_real?", stat_owned_real_p, MRB_ARGS_NONE());
}