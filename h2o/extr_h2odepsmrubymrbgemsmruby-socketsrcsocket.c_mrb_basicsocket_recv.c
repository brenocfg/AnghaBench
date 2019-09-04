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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;
typedef  int /*<<< orphan*/  fsize_t ;

/* Variables and functions */
 int /*<<< orphan*/  RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  mrb_str_buf_new (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mrb_str_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 
 int recv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  socket_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_basicsocket_recv(mrb_state *mrb, mrb_value self)
{
  ssize_t n;
  mrb_int maxlen, flags = 0;
  mrb_value buf;

  mrb_get_args(mrb, "i|i", &maxlen, &flags);
  buf = mrb_str_buf_new(mrb, maxlen);
  n = recv(socket_fd(mrb, self), RSTRING_PTR(buf), (fsize_t)maxlen, (int)flags);
  if (n == -1)
    mrb_sys_fail(mrb, "recv");
  mrb_str_resize(mrb, buf, (mrb_int)n);
  return buf;
}