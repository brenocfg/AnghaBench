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
typedef  scalar_t__ jerry_promise_state_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 scalar_t__ JERRY_ERROR_TYPE ; 
 scalar_t__ JERRY_PROMISE_STATE_PENDING ; 
 scalar_t__ JERRY_PROMISE_STATE_REJECTED ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  jerry_create_error (scalar_t__,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  jerry_create_number (int) ; 
 int /*<<< orphan*/  jerry_create_promise () ; 
 scalar_t__ jerry_get_error_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_get_promise_result (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_get_promise_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_get_value_from_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_resolve_or_reject_promise (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int jerry_value_is_object (int /*<<< orphan*/ ) ; 
 int jerry_value_is_undefined (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_promise_resolve_fail (void)
{
  jerry_value_t my_promise = jerry_create_promise ();

  // A created promise has an undefined promise result by default and a pending state
  {
    jerry_value_t promise_result = jerry_get_promise_result (my_promise);
    TEST_ASSERT (jerry_value_is_undefined (promise_result));

    jerry_promise_state_t promise_state = jerry_get_promise_state (my_promise);
    TEST_ASSERT (promise_state == JERRY_PROMISE_STATE_PENDING);

    jerry_release_value (promise_result);
  }

  // A resolved promise should have the result of from the resolve call and a fulfilled state
  {
    jerry_value_t error_value = jerry_create_error (JERRY_ERROR_TYPE, (const jerry_char_t *) "resolve_fail");
    jerry_value_t error_obj = jerry_get_value_from_error (error_value, true);
    jerry_value_t resolve_result = jerry_resolve_or_reject_promise (my_promise, error_obj, false);
    jerry_release_value (error_obj);

    jerry_value_t promise_result = jerry_get_promise_result (my_promise);
    // The error is not throw that's why it is only an error object.
    TEST_ASSERT (jerry_value_is_object (promise_result));
    TEST_ASSERT (jerry_get_error_type (promise_result) == JERRY_ERROR_TYPE);

    jerry_promise_state_t promise_state = jerry_get_promise_state (my_promise);
    TEST_ASSERT (promise_state == JERRY_PROMISE_STATE_REJECTED);

    jerry_release_value (promise_result);

    jerry_release_value (resolve_result);
  }

  // Resolvind a promise again does not change the result/state
  {
    jerry_value_t resolve_result = jerry_resolve_or_reject_promise (my_promise, jerry_create_number (50), true);

    jerry_value_t promise_result = jerry_get_promise_result (my_promise);
    TEST_ASSERT (jerry_value_is_object (promise_result));
    TEST_ASSERT (jerry_get_error_type (promise_result) == JERRY_ERROR_TYPE);

    jerry_promise_state_t promise_state = jerry_get_promise_state (my_promise);
    TEST_ASSERT (promise_state == JERRY_PROMISE_STATE_REJECTED);

    jerry_release_value (promise_result);

    jerry_release_value (resolve_result);
  }

  jerry_release_value (my_promise);
}