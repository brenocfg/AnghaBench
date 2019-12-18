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
typedef  int /*<<< orphan*/  const jerry_value_t ;
typedef  scalar_t__ jerry_length_t ;

/* Variables and functions */
 int /*<<< orphan*/  const jerry_create_undefined () ; 
 int /*<<< orphan*/  const jerry_get_resource_name (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/  const) ; 

jerry_value_t
jerryx_handler_resource_name (const jerry_value_t func_obj_val, /**< function object */
                              const jerry_value_t this_p, /**< this arg */
                              const jerry_value_t args_p[], /**< function arguments */
                              const jerry_length_t args_cnt) /**< number of function arguments */
{
  (void) func_obj_val; /* unused */
  (void) this_p; /* unused */

  jerry_value_t undefined_value = jerry_create_undefined ();
  jerry_value_t resource_name = jerry_get_resource_name (args_cnt > 0 ? args_p[0] : undefined_value);
  jerry_release_value (undefined_value);

  return resource_name;
}