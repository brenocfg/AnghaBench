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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  E_SOCKET_ERROR ; 
 int /*<<< orphan*/  NI_MAXHOST ; 
 int /*<<< orphan*/  NI_MAXSERV ; 
 scalar_t__ RSTRING_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getnameinfo (struct sockaddr*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_ary_new_capa (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_iv_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_buf_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_string_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 

__attribute__((used)) static mrb_value
mrb_addrinfo_getnameinfo(mrb_state *mrb, mrb_value self)
{
  mrb_int flags;
  mrb_value ary, host, sastr, serv;
  int error;

  flags = 0;
  mrb_get_args(mrb, "|i", &flags);
  host = mrb_str_buf_new(mrb, NI_MAXHOST);
  serv = mrb_str_buf_new(mrb, NI_MAXSERV);

  sastr = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@sockaddr"));
  if (!mrb_string_p(sastr)) {
    mrb_raise(mrb, E_SOCKET_ERROR, "invalid sockaddr");
  }
  error = getnameinfo((struct sockaddr *)RSTRING_PTR(sastr), (socklen_t)RSTRING_LEN(sastr), RSTRING_PTR(host), NI_MAXHOST, RSTRING_PTR(serv), NI_MAXSERV, (int)flags);
  if (error) {
    mrb_raisef(mrb, E_SOCKET_ERROR, "getnameinfo: %S", mrb_str_new_cstr(mrb, gai_strerror(error)));
  }
  ary = mrb_ary_new_capa(mrb, 2);
  mrb_str_resize(mrb, host, strlen(RSTRING_PTR(host)));
  mrb_ary_push(mrb, ary, host);
  mrb_str_resize(mrb, serv, strlen(RSTRING_PTR(serv)));
  mrb_ary_push(mrb, ary, serv);
  return ary;
}