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
 scalar_t__ RSTRING_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int bind (int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static mrb_value
mrb_socket_bind(mrb_state *mrb, mrb_value klass)
{
  mrb_value sastr;
  mrb_int s;

  mrb_get_args(mrb, "iS", &s, &sastr);
  if (bind((int)s, (struct sockaddr *)RSTRING_PTR(sastr), (socklen_t)RSTRING_LEN(sastr)) == -1) {
    mrb_sys_fail(mrb, "bind");
  }
  return mrb_nil_value();
}