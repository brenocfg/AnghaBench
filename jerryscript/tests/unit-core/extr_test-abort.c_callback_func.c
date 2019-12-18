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
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_UNUSED (int /*<<< orphan*/  const* const* const* const* const* const* const* const* const* const) ; 
 int /*<<< orphan*/  const* const* const* const* const* const******* jerry_create_abort_from_value (int /*<<< orphan*/  const* const* const* const* const* const* const* const*,int) ; 
 int /*<<< orphan*/  const* const* const* const* const* const******* jerry_create_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static jerry_value_t
callback_func (const jerry_value_t function_obj,
               const jerry_value_t this_val,
               const jerry_value_t args_p[],
               const jerry_length_t args_count)
{
  JERRY_UNUSED (function_obj);
  JERRY_UNUSED (this_val);
  JERRY_UNUSED (args_p);
  JERRY_UNUSED (args_count);

  jerry_value_t value = jerry_create_string ((jerry_char_t *) "Abort run!");
  value = jerry_create_abort_from_value (value, true);
  return value;
}