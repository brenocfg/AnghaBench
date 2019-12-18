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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  scalar_t__ jerry_length_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_UNUSED (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  jerry_get_backtrace (scalar_t__) ; 
 scalar_t__ jerry_get_number_value (int /*<<< orphan*/  const) ; 
 scalar_t__ jerry_value_is_number (int /*<<< orphan*/  const) ; 

__attribute__((used)) static jerry_value_t
backtrace_handler (const jerry_value_t function_obj, /**< function object */
                   const jerry_value_t this_val, /**< this value */
                   const jerry_value_t args_p[], /**< argument list */
                   const jerry_length_t args_count) /**< argument count */
{
  JERRY_UNUSED (function_obj);
  JERRY_UNUSED (this_val);

  uint32_t max_depth = 0;

  if (args_count > 0 && jerry_value_is_number (args_p[0]))
  {
    max_depth = (uint32_t) jerry_get_number_value (args_p[0]);
  }

  return jerry_get_backtrace (max_depth);
}