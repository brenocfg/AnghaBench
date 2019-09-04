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
typedef  int /*<<< orphan*/  mrb_bool ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_ary_new_from_values (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_bool_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_protect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  protect_cb ; 

__attribute__((used)) static mrb_value
run_protect(mrb_state *mrb, mrb_value self)
{
  mrb_value b;
  mrb_value ret[2];
  mrb_bool state;
  mrb_get_args(mrb, "&", &b);
  ret[0] = mrb_protect(mrb, protect_cb, b, &state);
  ret[1] = mrb_bool_value(state);
  return mrb_ary_new_from_values(mrb, 2, ret);
}