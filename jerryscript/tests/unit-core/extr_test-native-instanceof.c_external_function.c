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
typedef  int /*<<< orphan*/  jerry_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  jerry_create_undefined () ; 

__attribute__((used)) static jerry_value_t
external_function (const jerry_value_t function_obj,
                   const jerry_value_t this_arg,
                   const jerry_value_t args_p[],
                   const jerry_size_t args_count)
{
  (void) function_obj;
  (void) this_arg;
  (void) args_p;
  (void) args_count;

  return jerry_create_undefined ();
}