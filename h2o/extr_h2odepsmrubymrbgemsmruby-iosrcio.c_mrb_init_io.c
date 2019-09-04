#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct RClass {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  object_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_ARGS_ANY () ; 
 int /*<<< orphan*/  MRB_ARGS_NONE () ; 
 int /*<<< orphan*/  MRB_ARGS_REQ (int) ; 
 int /*<<< orphan*/  MRB_SET_INSTANCE_TT (struct RClass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRB_TT_DATA ; 
 struct RClass* mrb_define_class (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_class_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_gv_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_include_module (TYPE_1__*,struct RClass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_cstr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mrb_io_check_readable ; 
 int /*<<< orphan*/  mrb_io_close ; 
 int /*<<< orphan*/  mrb_io_close_on_exec_p ; 
 int /*<<< orphan*/  mrb_io_close_write ; 
 int /*<<< orphan*/  mrb_io_closed ; 
 int /*<<< orphan*/  mrb_io_fileno ; 
 int /*<<< orphan*/  mrb_io_initialize ; 
 int /*<<< orphan*/  mrb_io_initialize_copy ; 
 int /*<<< orphan*/  mrb_io_isatty ; 
 int /*<<< orphan*/  mrb_io_pid ; 
 int /*<<< orphan*/  mrb_io_s_for_fd ; 
 int /*<<< orphan*/  mrb_io_s_pipe ; 
 int /*<<< orphan*/  mrb_io_s_popen ; 
 int /*<<< orphan*/  mrb_io_s_select ; 
 int /*<<< orphan*/  mrb_io_s_sysclose ; 
 int /*<<< orphan*/  mrb_io_s_sysopen ; 
 int /*<<< orphan*/  mrb_io_set_close_on_exec ; 
 int /*<<< orphan*/  mrb_io_set_sync ; 
 int /*<<< orphan*/  mrb_io_sync ; 
 int /*<<< orphan*/  mrb_io_sysread ; 
 int /*<<< orphan*/  mrb_io_sysseek ; 
 int /*<<< orphan*/  mrb_io_syswrite ; 
 int /*<<< orphan*/  mrb_module_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (TYPE_1__*,char*) ; 

void
mrb_init_io(mrb_state *mrb)
{
  struct RClass *io;

  io      = mrb_define_class(mrb, "IO", mrb->object_class);
  MRB_SET_INSTANCE_TT(io, MRB_TT_DATA);

  mrb_include_module(mrb, io, mrb_module_get(mrb, "Enumerable")); /* 15.2.20.3 */
  mrb_define_class_method(mrb, io, "_popen",  mrb_io_s_popen,   MRB_ARGS_ANY());
  mrb_define_class_method(mrb, io, "_sysclose",  mrb_io_s_sysclose, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, io, "for_fd",  mrb_io_s_for_fd,   MRB_ARGS_ANY());
  mrb_define_class_method(mrb, io, "select",  mrb_io_s_select,  MRB_ARGS_ANY());
  mrb_define_class_method(mrb, io, "sysopen", mrb_io_s_sysopen, MRB_ARGS_ANY());
#if !defined(_WIN32) && !(defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE)
  mrb_define_class_method(mrb, io, "_pipe", mrb_io_s_pipe, MRB_ARGS_NONE());
#endif

  mrb_define_method(mrb, io, "initialize", mrb_io_initialize, MRB_ARGS_ANY());    /* 15.2.20.5.21 (x)*/
  mrb_define_method(mrb, io, "initialize_copy", mrb_io_initialize_copy, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, io, "_check_readable", mrb_io_check_readable, MRB_ARGS_NONE());
  mrb_define_method(mrb, io, "isatty",     mrb_io_isatty,     MRB_ARGS_NONE());
  mrb_define_method(mrb, io, "sync",       mrb_io_sync,       MRB_ARGS_NONE());
  mrb_define_method(mrb, io, "sync=",      mrb_io_set_sync,   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, io, "sysread",    mrb_io_sysread,    MRB_ARGS_ANY());
  mrb_define_method(mrb, io, "sysseek",    mrb_io_sysseek,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, io, "syswrite",   mrb_io_syswrite,   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, io, "close",      mrb_io_close,      MRB_ARGS_NONE());   /* 15.2.20.5.1 */
  mrb_define_method(mrb, io, "close_write",    mrb_io_close_write,       MRB_ARGS_NONE());
  mrb_define_method(mrb, io, "close_on_exec=", mrb_io_set_close_on_exec, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, io, "close_on_exec?", mrb_io_close_on_exec_p,   MRB_ARGS_NONE());
  mrb_define_method(mrb, io, "closed?",    mrb_io_closed,     MRB_ARGS_NONE());   /* 15.2.20.5.2 */
  mrb_define_method(mrb, io, "pid",        mrb_io_pid,        MRB_ARGS_NONE());   /* 15.2.20.5.2 */
  mrb_define_method(mrb, io, "fileno",     mrb_io_fileno,     MRB_ARGS_NONE());


  mrb_gv_set(mrb, mrb_intern_cstr(mrb, "$/"), mrb_str_new_cstr(mrb, "\n"));
}