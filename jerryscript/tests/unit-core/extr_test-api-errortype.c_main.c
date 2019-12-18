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
typedef  int /*<<< orphan*/  test_values ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  scalar_t__ jerry_error_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;
typedef  int /*<<< orphan*/  errors ;

/* Variables and functions */
 scalar_t__ JERRY_ERROR_COMMON ; 
 scalar_t__ JERRY_ERROR_EVAL ; 
 scalar_t__ JERRY_ERROR_NONE ; 
 scalar_t__ JERRY_ERROR_RANGE ; 
 scalar_t__ JERRY_ERROR_REFERENCE ; 
 scalar_t__ JERRY_ERROR_SYNTAX ; 
 scalar_t__ JERRY_ERROR_TYPE ; 
 scalar_t__ JERRY_ERROR_URI ; 
 int /*<<< orphan*/  JERRY_INIT_EMPTY ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_INIT () ; 
 int /*<<< orphan*/  jerry_cleanup () ; 
 int /*<<< orphan*/  jerry_create_boolean (int) ; 
 int /*<<< orphan*/  jerry_create_error (scalar_t__,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  jerry_create_number (int) ; 
 int /*<<< orphan*/  jerry_create_object () ; 
 int /*<<< orphan*/  jerry_create_string (int /*<<< orphan*/  const*) ; 
 scalar_t__ jerry_get_error_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_get_value_from_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jerry_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int jerry_value_is_error (int /*<<< orphan*/ ) ; 

int
main (void)
{
  TEST_INIT ();

  jerry_init (JERRY_INIT_EMPTY);

  jerry_error_t errors[] =
  {
    JERRY_ERROR_COMMON,
    JERRY_ERROR_EVAL,
    JERRY_ERROR_RANGE,
    JERRY_ERROR_REFERENCE,
    JERRY_ERROR_SYNTAX,
    JERRY_ERROR_TYPE,
    JERRY_ERROR_URI
  };

  for (size_t idx = 0; idx < sizeof (errors) / sizeof (errors[0]); idx++)
  {
    jerry_value_t error_obj = jerry_create_error (errors[idx], (const jerry_char_t *)"test");
    TEST_ASSERT (jerry_value_is_error (error_obj));
    TEST_ASSERT (jerry_get_error_type (error_obj) == errors[idx]);

    error_obj = jerry_get_value_from_error (error_obj, true);

    TEST_ASSERT (jerry_get_error_type (error_obj) == errors[idx]);

    jerry_release_value (error_obj);
  }

  jerry_value_t test_values[] =
  {
    jerry_create_number (11),
    jerry_create_string ((const jerry_char_t *) "message"),
    jerry_create_boolean (true),
    jerry_create_object (),
  };

  for (size_t idx = 0; idx < sizeof (test_values) / sizeof (test_values[0]); idx++)
  {
    jerry_error_t error_type = jerry_get_error_type (test_values[idx]);
    TEST_ASSERT (error_type == JERRY_ERROR_NONE);
    jerry_release_value (test_values[idx]);
  }

  jerry_cleanup ();
}