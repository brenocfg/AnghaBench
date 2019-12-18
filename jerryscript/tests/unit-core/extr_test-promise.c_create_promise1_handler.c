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
typedef  int /*<<< orphan*/  const* const* const* const* const* const* const* const* jerry_value_t ;
typedef  int /*<<< orphan*/  const* const* const* const* const* const* const* const* const* jerry_length_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_UNUSED (int /*<<< orphan*/  const* const* const* const* const* const* const* const* const* const) ; 
 int /*<<< orphan*/  jerry_acquire_value (int /*<<< orphan*/  const* const* const* const* const* const* const* const*) ; 
 int /*<<< orphan*/  const* const* const* const* const* const******* jerry_create_promise () ; 
 int /*<<< orphan*/  my_promise1 ; 

__attribute__((used)) static jerry_value_t
create_promise1_handler (const jerry_value_t func_obj_val, /**< function object */
                         const jerry_value_t this_val, /**< this value */
                         const jerry_value_t args_p[], /**< arguments list */
                         const jerry_length_t args_cnt) /**< arguments length */
{
  JERRY_UNUSED (func_obj_val);
  JERRY_UNUSED (this_val);
  JERRY_UNUSED (args_p);
  JERRY_UNUSED (args_cnt);

  jerry_value_t ret =  jerry_create_promise ();
  my_promise1 = jerry_acquire_value (ret);

  return ret;
}