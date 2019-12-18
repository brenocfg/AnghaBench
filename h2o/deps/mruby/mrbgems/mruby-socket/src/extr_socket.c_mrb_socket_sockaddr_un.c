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
struct sockaddr_un {int sun_len; char* sun_path; int /*<<< orphan*/  sun_family; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 int /*<<< orphan*/  E_NOTIMP_ERROR ; 
 size_t RSTRING_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_buf_new (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mrb_str_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static mrb_value
mrb_socket_sockaddr_un(mrb_state *mrb, mrb_value klass)
{
#ifdef _WIN32
  mrb_raise(mrb, E_NOTIMP_ERROR, "sockaddr_un unsupported on Windows");
  return mrb_nil_value();
#else
  struct sockaddr_un *sunp;
  mrb_value path, s;

  mrb_get_args(mrb, "S", &path);
  if ((size_t)RSTRING_LEN(path) > sizeof(sunp->sun_path) - 1) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "too long unix socket path (max: %S bytes)", mrb_fixnum_value(sizeof(sunp->sun_path) - 1));
  }
  s = mrb_str_buf_new(mrb, sizeof(struct sockaddr_un));
  sunp = (struct sockaddr_un *)RSTRING_PTR(s);
#if HAVE_SA_LEN
  sunp->sun_len = sizeof(struct sockaddr_un);
#endif
  sunp->sun_family = AF_UNIX;
  memcpy(sunp->sun_path, RSTRING_PTR(path), RSTRING_LEN(path));
  sunp->sun_path[RSTRING_LEN(path)] = '\0';
  mrb_str_resize(mrb, s, sizeof(struct sockaddr_un));
  return s;
#endif
}