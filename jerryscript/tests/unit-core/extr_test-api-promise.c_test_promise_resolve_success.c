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
 scalar_t__ JERRY_PROMISE_STATE_FULFILLED ; 
 scalar_t__ JERRY_PROMISE_STATE_PENDING ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  jerry_create_number (int) ; 
 int /*<<< orphan*/  jerry_create_object () ; 
 int /*<<< orphan*/  jerry_create_promise () ; 
 int /*<<< orphan*/  jerry_create_string (int /*<<< orphan*/  const*) ; 
 int jerry_get_boolean_value (int /*<<< orphan*/ ) ; 
 double jerry_get_number_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_get_promise_result (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_get_promise_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_get_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_resolve_or_reject_promise (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jerry_set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_value_is_boolean (int /*<<< orphan*/ ) ; 
 int jerry_value_is_number (int /*<<< orphan*/ ) ; 
 int jerry_value_is_object (int /*<<< orphan*/ ) ; 
 int jerry_value_is_undefined (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_promise_resolve_success (void)
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

  jerry_value_t resolve_value = jerry_create_object ();
  {
    jerry_value_t obj_key = jerry_create_string ((const jerry_char_t *) "key_one");
    jerry_value_t set_result = jerry_set_property (resolve_value, obj_key, jerry_create_number (3));
    TEST_ASSERT (jerry_value_is_boolean (set_result) && (jerry_get_boolean_value (set_result) == true));
    jerry_release_value (set_result);
    jerry_release_value (obj_key);
  }

  // A resolved promise should have the result of from the resolve call and a fulfilled state
  {
    jerry_value_t resolve_result = jerry_resolve_or_reject_promise (my_promise, resolve_value, true);

    // Release "old" value of resolve.
    jerry_release_value (resolve_value);

    jerry_value_t promise_result = jerry_get_promise_result (my_promise);
    {
      TEST_ASSERT (jerry_value_is_object (promise_result));
      jerry_value_t obj_key = jerry_create_string ((const jerry_char_t *) "key_one");
      jerry_value_t get_result = jerry_get_property (promise_result, obj_key);
      TEST_ASSERT (jerry_value_is_number (get_result));
      TEST_ASSERT (jerry_get_number_value (get_result) == 3.0);

      jerry_release_value (get_result);
      jerry_release_value (obj_key);
    }

    jerry_promise_state_t promise_state = jerry_get_promise_state (my_promise);
    TEST_ASSERT (promise_state == JERRY_PROMISE_STATE_FULFILLED);

    jerry_release_value (promise_result);

    jerry_release_value (resolve_result);
  }

  // Resolvind a promise again does not change the result/state
  {
    jerry_value_t resolve_result = jerry_resolve_or_reject_promise (my_promise, jerry_create_number (50), false);

    jerry_value_t promise_result = jerry_get_promise_result (my_promise);
    {
      TEST_ASSERT (jerry_value_is_object (promise_result));
      jerry_value_t obj_key = jerry_create_string ((const jerry_char_t *) "key_one");
      jerry_value_t get_result = jerry_get_property (promise_result, obj_key);
      TEST_ASSERT (jerry_value_is_number (get_result));
      TEST_ASSERT (jerry_get_number_value (get_result) == 3.0);

      jerry_release_value (get_result);
      jerry_release_value (obj_key);
    }

    jerry_promise_state_t promise_state = jerry_get_promise_state (my_promise);
    TEST_ASSERT (promise_state == JERRY_PROMISE_STATE_FULFILLED);

    jerry_release_value (promise_result);

    jerry_release_value (resolve_result);
  }

  jerry_release_value (my_promise);
}