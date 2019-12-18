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
typedef  int mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
check_pos_arg(mrb_state *mrb, mrb_int posarg, mrb_int n)
{
  if (posarg > 0) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "numbered(%S) after unnumbered(%S)",
               mrb_fixnum_value(n), mrb_fixnum_value(posarg));
  }
  if (posarg == -2) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "numbered(%S) after named", mrb_fixnum_value(n));
  }
  if (n < 1) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "invalid index - %S$", mrb_fixnum_value(n));
  }
}