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
 int /*<<< orphan*/  jerry_create_boolean (int) ; 

__attribute__((used)) static jerry_value_t
test_ext_function (const jerry_value_t function_obj, /**< function object */
                   const jerry_value_t this_val, /**< function this value */
                   const jerry_value_t args_p[], /**< array of arguments */
                   const jerry_length_t args_cnt) /**< number of arguments */
{
  (void) function_obj;
  (void) this_val;
  (void) args_p;
  (void) args_cnt;
  return jerry_create_boolean (true);
}