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
 int jerry_get_boolean_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int jerry_value_is_boolean (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
assert_boolean_and_release (jerry_value_t result, bool expected)
{
  TEST_ASSERT (jerry_value_is_boolean (result));
  TEST_ASSERT (jerry_get_boolean_value (result) == expected);
  jerry_release_value (result);
}