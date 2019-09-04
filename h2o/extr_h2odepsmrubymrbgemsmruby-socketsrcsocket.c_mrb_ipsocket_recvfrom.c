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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  ss ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;
typedef  int /*<<< orphan*/  fsize_t ;

/* Variables and functions */
 int /*<<< orphan*/  RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_new_capa (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  mrb_str_buf_new (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mrb_str_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 
 int recvfrom (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  sa2addrlist (int /*<<< orphan*/ *,struct sockaddr*,int) ; 
 int socket_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_ipsocket_recvfrom(mrb_state *mrb, mrb_value self)
{
  struct sockaddr_storage ss;
  socklen_t socklen;
  mrb_value a, buf, pair;
  mrb_int flags, maxlen;
  ssize_t n;
  int fd;

  fd = socket_fd(mrb, self);
  flags = 0;
  mrb_get_args(mrb, "i|i", &maxlen, &flags);
  buf = mrb_str_buf_new(mrb, maxlen);
  socklen = sizeof(ss);
  n = recvfrom(fd, RSTRING_PTR(buf), (fsize_t)maxlen, (int)flags,
  	       (struct sockaddr *)&ss, &socklen);
  if (n == -1) {
    mrb_sys_fail(mrb, "recvfrom");
  }
  mrb_str_resize(mrb, buf, (mrb_int)n);
  a = sa2addrlist(mrb, (struct sockaddr *)&ss, socklen);
  pair = mrb_ary_new_capa(mrb, 2);
  mrb_ary_push(mrb, pair, buf);
  mrb_ary_push(mrb, pair, a);
  return pair;
}