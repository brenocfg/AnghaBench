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

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 double jerry_get_number_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_value_is_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
assert_number (jerry_value_t js_value, double expected_result)
{
  TEST_ASSERT (!jerry_value_is_error (js_value));
  TEST_ASSERT (jerry_get_number_value (js_value) == expected_result);
}