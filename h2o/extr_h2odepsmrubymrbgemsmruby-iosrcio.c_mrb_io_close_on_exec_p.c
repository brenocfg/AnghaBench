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
 int /*<<< orphan*/  mrb_false_value () ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

mrb_value
mrb_io_close_on_exec_p(mrb_state *mrb, mrb_value self)
{
#if defined(F_GETFD) && defined(F_SETFD) && defined(FD_CLOEXEC)
  struct mrb_io *fptr;
  int ret;

  fptr = io_get_open_fptr(mrb, self);

  if (fptr->fd2 >= 0) {
    if ((ret = fcntl(fptr->fd2, F_GETFD)) == -1) mrb_sys_fail(mrb, "F_GETFD failed");
    if (!(ret & FD_CLOEXEC)) return mrb_false_value();
  }

  if ((ret = fcntl(fptr->fd, F_GETFD)) == -1) mrb_sys_fail(mrb, "F_GETFD failed");
  if (!(ret & FD_CLOEXEC)) return mrb_false_value();
  return mrb_true_value();

#else
  mrb_raise(mrb, E_NOTIMP_ERROR, "IO#close_on_exec? is not supported on the platform");
  return mrb_false_value();
#endif
}