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
typedef  int /*<<< orphan*/  test_source ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  char jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_PARSE_NO_OPTS ; 
 scalar_t__ JERRY_PROMISE_STATE_FULFILLED ; 
 scalar_t__ JERRY_PROMISE_STATE_PENDING ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 double jerry_get_number_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_get_promise_result (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_get_promise_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_run_all_enqueued_jobs () ; 
 int /*<<< orphan*/  jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int jerry_value_is_number (int /*<<< orphan*/ ) ; 
 int jerry_value_is_promise (int /*<<< orphan*/ ) ; 
 int jerry_value_is_undefined (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_promise_from_js (void)
{
  const jerry_char_t test_source[] = "(new Promise(function(rs, rj) { rs(30); })).then(function(v) { return v + 1; })";

  jerry_value_t parsed_code_val = jerry_parse (NULL,
                                               0,
                                               test_source,
                                               sizeof (test_source) - 1,
                                               JERRY_PARSE_NO_OPTS);
  TEST_ASSERT (!jerry_value_is_error (parsed_code_val));

  jerry_value_t res = jerry_run (parsed_code_val);
  TEST_ASSERT (jerry_value_is_promise (res));

  TEST_ASSERT (jerry_get_promise_state (res) == JERRY_PROMISE_STATE_PENDING);

  jerry_value_t run_result = jerry_run_all_enqueued_jobs ();
  TEST_ASSERT (jerry_value_is_undefined (run_result));
  jerry_release_value (run_result);

  TEST_ASSERT (jerry_get_promise_state (res) == JERRY_PROMISE_STATE_FULFILLED);
  jerry_value_t promise_result = jerry_get_promise_result (res);
  TEST_ASSERT (jerry_value_is_number (promise_result));
  TEST_ASSERT (jerry_get_number_value (promise_result) == 31.0);

  jerry_release_value (promise_result);
  jerry_release_value (res);
  jerry_release_value (parsed_code_val);
}