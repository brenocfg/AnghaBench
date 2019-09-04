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
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_next_arg(mrb_state *mrb, int posarg, int nextarg)
{
  switch (posarg) {
  case -1:
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "unnumbered(%S) mixed with numbered", mrb_fixnum_value(nextarg));
    break;
  case -2:
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "unnumbered(%S) mixed with named", mrb_fixnum_value(nextarg));
    break;
  default:
    break;
  }
}