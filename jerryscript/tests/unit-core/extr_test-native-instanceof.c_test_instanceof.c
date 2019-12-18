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
 int /*<<< orphan*/  jerry_call_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jerry_construct_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_create_undefined () ; 
 int jerry_get_boolean_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int jerry_value_is_boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_value_is_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_instanceof (jerry_value_t instanceof,
                 jerry_value_t constructor)
{
  jerry_value_t instance = jerry_construct_object (constructor, NULL, 0);
  jerry_value_t args[2] =
  {
    instance, constructor
  };

  jerry_value_t undefined = jerry_create_undefined ();
  jerry_value_t result = jerry_call_function (instanceof, undefined, args, 2);
  jerry_release_value (undefined);

  TEST_ASSERT (!jerry_value_is_error (result));
  TEST_ASSERT (jerry_value_is_boolean (result));

  TEST_ASSERT (jerry_get_boolean_value (result));

  jerry_release_value (instance);
  jerry_release_value (result);
}