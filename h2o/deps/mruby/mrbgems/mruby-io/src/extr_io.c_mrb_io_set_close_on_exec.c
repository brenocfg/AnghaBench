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
struct mrb_io {scalar_t__ fd2; scalar_t__ fd; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_bool ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMP_ERROR ; 
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  F_SETFD ; 
 int fcntl (scalar_t__,int /*<<< orphan*/ ,...) ; 
 struct mrb_io* io_get_open_fptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_bool_value (scalar_t__) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 

mrb_value
mrb_io_set_close_on_exec(mrb_state *mrb, mrb_value self)
{
#if defined(F_GETFD) && defined(F_SETFD) && defined(FD_CLOEXEC)
  struct mrb_io *fptr;
  int flag, ret;
  mrb_bool b;

  fptr = io_get_open_fptr(mrb, self);
  mrb_get_args(mrb, "b", &b);
  flag = b ? FD_CLOEXEC : 0;

  if (fptr->fd2 >= 0) {
    if ((ret = fcntl(fptr->fd2, F_GETFD)) == -1) mrb_sys_fail(mrb, "F_GETFD failed");
    if ((ret & FD_CLOEXEC) != flag) {
      ret = (ret & ~FD_CLOEXEC) | flag;
      ret = fcntl(fptr->fd2, F_SETFD, ret);

      if (ret == -1) mrb_sys_fail(mrb, "F_SETFD failed");
    }
  }

  if ((ret = fcntl(fptr->fd, F_GETFD)) == -1) mrb_sys_fail(mrb, "F_GETFD failed");
  if ((ret & FD_CLOEXEC) != flag) {
    ret = (ret & ~FD_CLOEXEC) | flag;
    ret = fcntl(fptr->fd, F_SETFD, ret);
    if (ret == -1) mrb_sys_fail(mrb, "F_SETFD failed");
  }

  return mrb_bool_value(b);
#else
  mrb_raise(mrb, E_NOTIMP_ERROR, "IO#close_on_exec= is not supported on the platform");
  return mrb_nil_value();
#endif
}