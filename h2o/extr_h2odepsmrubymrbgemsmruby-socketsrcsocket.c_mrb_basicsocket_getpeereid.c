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
 int /*<<< orphan*/  E_RUNTIME_ERROR ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static mrb_value
mrb_basicsocket_getpeereid(mrb_state *mrb, mrb_value self)
{
#ifdef HAVE_GETPEEREID
  mrb_value ary;
  gid_t egid;
  uid_t euid;
  int s;

  s = socket_fd(mrb, self);
  if (getpeereid(s, &euid, &egid) != 0)
    mrb_sys_fail(mrb, "getpeereid");

  ary = mrb_ary_new_capa(mrb, 2);
  mrb_ary_push(mrb, ary, mrb_fixnum_value((mrb_int)euid));
  mrb_ary_push(mrb, ary, mrb_fixnum_value((mrb_int)egid));
  return ary;
#else
  mrb_raise(mrb, E_RUNTIME_ERROR, "getpeereid is not available on this system");
  return mrb_nil_value();
#endif
}