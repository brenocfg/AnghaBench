#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct RClass {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  object_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int MRB_ARGS_NONE () ; 
 int MRB_ARGS_OPT (int) ; 
 int MRB_ARGS_REQ (int) ; 
 int /*<<< orphan*/  MRB_SET_INSTANCE_TT (struct RClass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRB_TT_DATA ; 
 struct RClass* mrb_define_class (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_class_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_dir_chdir ; 
 int /*<<< orphan*/  mrb_dir_chroot ; 
 int /*<<< orphan*/  mrb_dir_close ; 
 int /*<<< orphan*/  mrb_dir_delete ; 
 int /*<<< orphan*/  mrb_dir_existp ; 
 int /*<<< orphan*/  mrb_dir_getwd ; 
 int /*<<< orphan*/  mrb_dir_init ; 
 int /*<<< orphan*/  mrb_dir_mkdir ; 
 int /*<<< orphan*/  mrb_dir_read ; 
 int /*<<< orphan*/  mrb_dir_rewind ; 
 int /*<<< orphan*/  mrb_dir_seek ; 
 int /*<<< orphan*/  mrb_dir_tell ; 

void
mrb_mruby_dir_gem_init(mrb_state *mrb)
{
  struct RClass *d;

  d = mrb_define_class(mrb, "Dir", mrb->object_class);
  MRB_SET_INSTANCE_TT(d, MRB_TT_DATA);
  mrb_define_class_method(mrb, d, "delete", mrb_dir_delete, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, d, "exist?", mrb_dir_existp, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, d, "getwd",  mrb_dir_getwd,  MRB_ARGS_NONE());
  mrb_define_class_method(mrb, d, "mkdir",  mrb_dir_mkdir,  MRB_ARGS_REQ(1)|MRB_ARGS_OPT(1));
  mrb_define_class_method(mrb, d, "_chdir", mrb_dir_chdir,  MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, d, "chroot", mrb_dir_chroot, MRB_ARGS_REQ(1));

  mrb_define_method(mrb, d, "close",      mrb_dir_close,  MRB_ARGS_NONE());
  mrb_define_method(mrb, d, "initialize", mrb_dir_init,   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, d, "read",       mrb_dir_read,   MRB_ARGS_NONE());
  mrb_define_method(mrb, d, "rewind",     mrb_dir_rewind, MRB_ARGS_NONE());
  mrb_define_method(mrb, d, "seek",       mrb_dir_seek,   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, d, "tell",       mrb_dir_tell,   MRB_ARGS_NONE());
}