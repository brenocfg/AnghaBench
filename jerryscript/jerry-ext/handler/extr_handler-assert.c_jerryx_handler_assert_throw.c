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
typedef  int jerry_length_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_ERROR_COMMON ; 
 int /*<<< orphan*/  jerry_create_boolean (int) ; 
 int /*<<< orphan*/  jerry_create_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ jerry_get_boolean_value (int /*<<< orphan*/  const) ; 
 scalar_t__ jerry_value_is_boolean (int /*<<< orphan*/  const) ; 

jerry_value_t
jerryx_handler_assert_throw (const jerry_value_t func_obj_val, /**< function object */
                             const jerry_value_t this_p, /**< this arg */
                             const jerry_value_t args_p[], /**< function arguments */
                             const jerry_length_t args_cnt) /**< number of function arguments */
{
  (void) func_obj_val; /* unused */
  (void) this_p; /* unused */

  if (args_cnt == 1
      && jerry_value_is_boolean (args_p[0])
      && jerry_get_boolean_value (args_p[0]))
  {
    return jerry_create_boolean (true);
  }

  return jerry_create_error (JERRY_ERROR_COMMON, (jerry_char_t *) "assertion failed");
}