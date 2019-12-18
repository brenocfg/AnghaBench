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
typedef  char jerry_char_t ;
typedef  int /*<<< orphan*/  is_equal_src ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_PARSE_NO_OPTS ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  jerry_call_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jerry_create_undefined () ; 
 int /*<<< orphan*/  jerry_eval (char const*,int,int /*<<< orphan*/ ) ; 
 int jerry_get_boolean_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int jerry_value_is_boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_value_is_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
strict_equals (jerry_value_t a, /**< the first string to compare */
               jerry_value_t b) /**< the second string to compare */
{
  const jerry_char_t is_equal_src[] = "var isEqual = function(a, b) { return (a === b); }; isEqual";
  jerry_value_t is_equal_fn_val = jerry_eval (is_equal_src, sizeof (is_equal_src) - 1, JERRY_PARSE_NO_OPTS);
  TEST_ASSERT (!jerry_value_is_error (is_equal_fn_val));
  jerry_value_t args[2] = {a, b};
  jerry_value_t res = jerry_call_function (is_equal_fn_val, jerry_create_undefined (), args, 2);
  TEST_ASSERT (!jerry_value_is_error (res));
  TEST_ASSERT (jerry_value_is_boolean (res));
  bool is_strict_equal = jerry_get_boolean_value (res);
  jerry_release_value (res);
  jerry_release_value (is_equal_fn_val);
  return is_strict_equal;
}