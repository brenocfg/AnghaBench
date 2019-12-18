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
struct sockaddr_in6 {unsigned short sin6_port; } ;
struct sockaddr_in {unsigned short sin_port; } ;
struct sockaddr {int sa_family; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 int /*<<< orphan*/  NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 int /*<<< orphan*/  RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int getnameinfo (struct sockaddr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_new_capa (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (unsigned short) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_str_buf_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  mrb_str_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 
 unsigned short ntohs (unsigned short) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
sa2addrlist(mrb_state *mrb, const struct sockaddr *sa, socklen_t salen)
{
  mrb_value ary, host;
  unsigned short port;
  const char *afstr;

  switch (sa->sa_family) {
  case AF_INET:
    afstr = "AF_INET";
    port = ((struct sockaddr_in *)sa)->sin_port;
    break;
  case AF_INET6:
    afstr = "AF_INET6";
    port = ((struct sockaddr_in6 *)sa)->sin6_port;
    break;
  default:
    mrb_raise(mrb, E_ARGUMENT_ERROR, "bad af");
    return mrb_nil_value();
  }
  port = ntohs(port);
  host = mrb_str_buf_new(mrb, NI_MAXHOST);
  if (getnameinfo(sa, salen, RSTRING_PTR(host), NI_MAXHOST, NULL, 0, NI_NUMERICHOST) == -1)
    mrb_sys_fail(mrb, "getnameinfo");
  mrb_str_resize(mrb, host, strlen(RSTRING_PTR(host)));
  ary = mrb_ary_new_capa(mrb, 4);
  mrb_ary_push(mrb, ary, mrb_str_new_cstr(mrb, afstr));
  mrb_ary_push(mrb, ary, mrb_fixnum_value(port));
  mrb_ary_push(mrb, ary, host);
  mrb_ary_push(mrb, ary, host);
  return ary;
}