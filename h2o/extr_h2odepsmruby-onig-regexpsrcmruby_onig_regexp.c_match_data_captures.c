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
 scalar_t__ RARRAY_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ RARRAY_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_data_to_a (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_new_from_values (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static mrb_value
match_data_captures(mrb_state* mrb, mrb_value self) {
  mrb_value ary = match_data_to_a(mrb, self);
  return mrb_ary_new_from_values(mrb, RARRAY_LEN(ary) - 1, RARRAY_PTR(ary) + 1);
}