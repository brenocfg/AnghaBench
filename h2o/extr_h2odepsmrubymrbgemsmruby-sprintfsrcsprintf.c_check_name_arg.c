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
typedef  int /*<<< orphan*/  mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mrb_str_new (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_name_arg(mrb_state *mrb, int posarg, const char *name, mrb_int len)
{
  if (posarg > 0) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "named%S after unnumbered(%S)",
               mrb_str_new(mrb, (name), (len)), mrb_fixnum_value(posarg));
  }
  if (posarg == -1) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "named%S after numbered", mrb_str_new(mrb, (name), (len)));
  }
}