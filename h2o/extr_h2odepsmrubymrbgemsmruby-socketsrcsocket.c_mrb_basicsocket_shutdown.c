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
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 scalar_t__ SHUT_RDWR ; 
 int /*<<< orphan*/  mrb_fixnum_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ shutdown (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  socket_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_basicsocket_shutdown(mrb_state *mrb, mrb_value self)
{
  mrb_int how = SHUT_RDWR;

  mrb_get_args(mrb, "|i", &how);
  if (shutdown(socket_fd(mrb, self), (int)how) != 0)
    mrb_sys_fail(mrb, "shutdown");
  return mrb_fixnum_value(0);
}