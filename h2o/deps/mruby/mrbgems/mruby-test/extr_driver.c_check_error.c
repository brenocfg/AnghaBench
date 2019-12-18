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
 scalar_t__ mrb_fixnum (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_fixnum_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_gv_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
check_error(mrb_state *mrb)
{
  /* Error check */
  /* $ko_test and $kill_test should be 0 */
  mrb_value ko_test = mrb_gv_get(mrb, mrb_intern_lit(mrb, "$ko_test"));
  mrb_value kill_test = mrb_gv_get(mrb, mrb_intern_lit(mrb, "$kill_test"));

  return mrb_fixnum_p(ko_test) && mrb_fixnum(ko_test) == 0 && mrb_fixnum_p(kill_test) && mrb_fixnum(kill_test) == 0;
}