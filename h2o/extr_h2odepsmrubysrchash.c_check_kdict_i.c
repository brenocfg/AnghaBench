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
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_symbol_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_kdict_i(mrb_state *mrb, mrb_value key, mrb_value val, void *data)
{
  if (!mrb_symbol_p(key)) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "keyword argument hash with non symbol keys");
  }
  return 0;
}