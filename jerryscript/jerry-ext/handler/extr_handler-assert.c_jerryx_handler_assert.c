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
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  int /*<<< orphan*/  jerry_length_t ;

/* Variables and functions */
 int /*<<< orphan*/  jerryx_handler_assert_fatal (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const*,int /*<<< orphan*/  const) ; 

jerry_value_t
jerryx_handler_assert (const jerry_value_t func_obj_val, /**< function object */
                       const jerry_value_t this_p, /**< this arg */
                       const jerry_value_t args_p[], /**< function arguments */
                       const jerry_length_t args_cnt) /**< number of function arguments */
{
  return jerryx_handler_assert_fatal (func_obj_val, this_p, args_p, args_cnt);
}