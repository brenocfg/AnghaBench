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
 int /*<<< orphan*/  E_FROZEN_ERROR ; 
 scalar_t__ MRB_FROZEN_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_basic_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_write_barrier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mrb_struct_modify(mrb_state *mrb, mrb_value strct)
{
  if (MRB_FROZEN_P(mrb_basic_ptr(strct))) {
    mrb_raise(mrb, E_FROZEN_ERROR, "can't modify frozen struct");
  }

  mrb_write_barrier(mrb, mrb_basic_ptr(strct));
}