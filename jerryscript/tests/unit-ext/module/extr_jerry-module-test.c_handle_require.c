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

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  jerryx_module_resolve (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resolvers ; 

__attribute__((used)) static jerry_value_t
handle_require (const jerry_value_t js_function,
                const jerry_value_t this_val,
                const jerry_value_t args_p[],
                const jerry_length_t args_count)
{
  (void) js_function;
  (void) this_val;
  (void) args_count;

  jerry_value_t return_value = 0;

  TEST_ASSERT (args_count == 1);
  return_value = jerryx_module_resolve (args_p[0], resolvers, 3);

  return return_value;
}