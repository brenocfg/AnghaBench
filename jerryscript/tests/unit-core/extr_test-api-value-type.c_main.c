#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  test_eval_function ;
struct TYPE_3__ {scalar_t__ type_info; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ test_entry_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  scalar_t__ jerry_type_t ;
typedef  char const jerry_char_t ;
typedef  int /*<<< orphan*/  entries ;

/* Variables and functions */
 TYPE_1__ ENTRY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JERRY_ERROR_TYPE ; 
 int /*<<< orphan*/  JERRY_FEATURE_SYMBOL ; 
 int /*<<< orphan*/  JERRY_INIT_EMPTY ; 
 int /*<<< orphan*/  JERRY_PARSE_NO_OPTS ; 
 int /*<<< orphan*/  JERRY_TYPE_BOOLEAN ; 
 int /*<<< orphan*/  JERRY_TYPE_ERROR ; 
 int /*<<< orphan*/  JERRY_TYPE_FUNCTION ; 
 scalar_t__ JERRY_TYPE_NONE ; 
 int /*<<< orphan*/  JERRY_TYPE_NULL ; 
 int /*<<< orphan*/  JERRY_TYPE_NUMBER ; 
 int /*<<< orphan*/  JERRY_TYPE_OBJECT ; 
 int /*<<< orphan*/  JERRY_TYPE_STRING ; 
 scalar_t__ JERRY_TYPE_SYMBOL ; 
 int /*<<< orphan*/  JERRY_TYPE_UNDEFINED ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_INIT () ; 
 int /*<<< orphan*/  jerry_cleanup () ; 
 int /*<<< orphan*/  jerry_create_array (int) ; 
 int /*<<< orphan*/  jerry_create_boolean (int) ; 
 int /*<<< orphan*/  jerry_create_error (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  jerry_create_external_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_create_null () ; 
 int /*<<< orphan*/  jerry_create_number (int) ; 
 int /*<<< orphan*/  jerry_create_number_infinity (int) ; 
 int /*<<< orphan*/  jerry_create_number_nan () ; 
 int /*<<< orphan*/  jerry_create_object () ; 
 int /*<<< orphan*/  jerry_create_string (char const*) ; 
 int /*<<< orphan*/  jerry_create_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_create_undefined () ; 
 int /*<<< orphan*/  jerry_eval (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_init (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_is_feature_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_value_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_ext_function ; 

int
main (void)
{
  TEST_INIT ();

  jerry_init (JERRY_INIT_EMPTY);

  const jerry_char_t test_eval_function[] = "function demo(a) { return a + 1; }; demo";

  test_entry_t entries[] =
  {
    ENTRY (JERRY_TYPE_NUMBER, jerry_create_number (-33.0)),
    ENTRY (JERRY_TYPE_NUMBER, jerry_create_number (3)),
    ENTRY (JERRY_TYPE_NUMBER, jerry_create_number_nan ()),
    ENTRY (JERRY_TYPE_NUMBER, jerry_create_number_infinity (false)),
    ENTRY (JERRY_TYPE_NUMBER, jerry_create_number_infinity (true)),

    ENTRY (JERRY_TYPE_BOOLEAN, jerry_create_boolean (true)),
    ENTRY (JERRY_TYPE_BOOLEAN, jerry_create_boolean (false)),

    ENTRY (JERRY_TYPE_UNDEFINED, jerry_create_undefined ()),

    ENTRY (JERRY_TYPE_OBJECT, jerry_create_object ()),
    ENTRY (JERRY_TYPE_OBJECT, jerry_create_array (10)),
    ENTRY (JERRY_TYPE_ERROR, jerry_create_error (JERRY_ERROR_TYPE, (const jerry_char_t *) "error")),

    ENTRY (JERRY_TYPE_NULL, jerry_create_null ()),

    ENTRY (JERRY_TYPE_FUNCTION, jerry_eval (test_eval_function,
                                            sizeof (test_eval_function) - 1,
                                            JERRY_PARSE_NO_OPTS)),
    ENTRY (JERRY_TYPE_FUNCTION, jerry_create_external_function (test_ext_function)),

    ENTRY (JERRY_TYPE_STRING, jerry_create_string (test_eval_function)),
    ENTRY (JERRY_TYPE_STRING, jerry_create_string ((jerry_char_t *) "")),
  };

  for (size_t idx = 0; idx < sizeof (entries) / sizeof (entries[0]); idx++)
  {
    jerry_type_t type_info = jerry_value_get_type (entries[idx].value);

    TEST_ASSERT (type_info != JERRY_TYPE_NONE);
    TEST_ASSERT (type_info == entries[idx].type_info);

    jerry_release_value (entries[idx].value);
  }

  if (jerry_is_feature_enabled (JERRY_FEATURE_SYMBOL))
  {
    jerry_value_t symbol_desc_value = jerry_create_string ((jerry_char_t *) "foo");
    jerry_value_t symbol_value = jerry_create_symbol (symbol_desc_value);
    jerry_type_t type_info = jerry_value_get_type (symbol_value);

    TEST_ASSERT (type_info != JERRY_TYPE_NONE);
    TEST_ASSERT (type_info == JERRY_TYPE_SYMBOL);

    jerry_release_value (symbol_value);
    jerry_release_value (symbol_desc_value);
  }

  jerry_cleanup ();

  return 0;
}