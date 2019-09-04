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
struct mrb_io {int /*<<< orphan*/  is_socket; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_bool ;

/* Variables and functions */
 scalar_t__ DATA_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_bool_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static mrb_value
mrb_basicsocket_set_is_socket(mrb_state *mrb, mrb_value self)
{
  mrb_bool b;
  struct mrb_io *io_p;
  mrb_get_args(mrb, "b", &b);

  io_p = (struct mrb_io*)DATA_PTR(self);
  if (io_p) {
    io_p->is_socket = b;
  }

  return mrb_bool_value(b);
}