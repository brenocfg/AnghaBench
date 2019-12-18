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
struct mrb_io {int /*<<< orphan*/  fd; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;
typedef  int /*<<< orphan*/  mrb_float ;

/* Variables and functions */
 int /*<<< orphan*/  E_IO_ERROR ; 
 int MRB_INT_MAX ; 
 struct mrb_io* io_get_open_fptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lseek (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_float_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 

mrb_value
mrb_io_sysseek(mrb_state *mrb, mrb_value io)
{
  struct mrb_io *fptr;
  off_t pos;
  mrb_int offset, whence = -1;

  mrb_get_args(mrb, "i|i", &offset, &whence);
  if (whence < 0) {
    whence = 0;
  }

  fptr = io_get_open_fptr(mrb, io);
  pos = lseek(fptr->fd, (off_t)offset, (int)whence);
  if (pos == -1) {
    mrb_sys_fail(mrb, "sysseek");
  }
  if (pos > MRB_INT_MAX) {
#ifndef MRB_WITHOUT_FLOAT
    return mrb_float_value(mrb, (mrb_float)pos);
#else
    mrb_raise(mrb, E_IO_ERROR, "sysseek reached too far for MRB_WITHOUT_FLOAT");
#endif
  } else {
    return mrb_fixnum_value(pos);
  }
}