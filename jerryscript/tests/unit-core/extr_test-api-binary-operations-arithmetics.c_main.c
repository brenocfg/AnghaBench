#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  tests ;
typedef  int /*<<< orphan*/  test_nans ;
struct TYPE_8__ {int /*<<< orphan*/  rhs; int /*<<< orphan*/  lhs; int /*<<< orphan*/  op; } ;
typedef  TYPE_1__ test_nan_entry_t ;
typedef  TYPE_1__ test_error_entry_t ;
struct TYPE_9__ {int /*<<< orphan*/  op; int /*<<< orphan*/  expected; int /*<<< orphan*/  rhs; int /*<<< orphan*/  lhs; } ;
typedef  TYPE_3__ test_entry_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;
typedef  int /*<<< orphan*/  error_tests ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_BIN_OP_ADD ; 
 int /*<<< orphan*/  JERRY_BIN_OP_DIV ; 
 int /*<<< orphan*/  JERRY_BIN_OP_MUL ; 
 int /*<<< orphan*/  JERRY_BIN_OP_REM ; 
 int /*<<< orphan*/  JERRY_BIN_OP_STRICT_EQUAL ; 
 int /*<<< orphan*/  JERRY_BIN_OP_SUB ; 
 int /*<<< orphan*/  JERRY_ERROR_SYNTAX ; 
 int /*<<< orphan*/  JERRY_INIT_EMPTY ; 
 int /*<<< orphan*/  JERRY_PARSE_NO_OPTS ; 
 TYPE_3__ T (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_INIT () ; 
 TYPE_1__ T_ARI (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ T_ERR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ T_NAN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_acquire_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_binary_operation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_cleanup () ; 
 int /*<<< orphan*/  jerry_create_boolean (int) ; 
 int /*<<< orphan*/  jerry_create_error (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  jerry_create_null () ; 
 int /*<<< orphan*/  jerry_create_number (double) ; 
 int /*<<< orphan*/  jerry_create_number_infinity (int) ; 
 int /*<<< orphan*/  jerry_create_string (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  jerry_create_undefined () ; 
 int /*<<< orphan*/  jerry_eval (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_get_boolean_value (int /*<<< orphan*/ ) ; 
 double jerry_get_number_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_value_is_boolean (int /*<<< orphan*/ ) ; 
 int jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int jerry_value_is_number (int /*<<< orphan*/ ) ; 

int
main (void)
{
  TEST_INIT ();

  jerry_init (JERRY_INIT_EMPTY);

  jerry_value_t obj1 = jerry_eval ((const jerry_char_t *) "o={x:1};o", 9, JERRY_PARSE_NO_OPTS);
  jerry_value_t obj2 = jerry_eval ((const jerry_char_t *) "o={x:1};o", 9, JERRY_PARSE_NO_OPTS);
  jerry_value_t err1 = jerry_create_error (JERRY_ERROR_SYNTAX, (const jerry_char_t *) "error");

  test_nan_entry_t test_nans[] =
  {
    /* Testing addition (+) */
    T_NAN (JERRY_BIN_OP_ADD, jerry_create_number (3.1), jerry_create_undefined ()),
    T_NAN (JERRY_BIN_OP_ADD, jerry_create_undefined (), jerry_create_undefined ()),
    T_NAN (JERRY_BIN_OP_ADD, jerry_create_undefined (), jerry_create_null ()),

    /* Testing subtraction (-), multiplication (*), division (/), remainder (%) */
    T_ARI (jerry_create_number (3.1), jerry_create_undefined ()),
    T_ARI (jerry_create_string ((const jerry_char_t *) "foo"), jerry_create_string ((const jerry_char_t *) "bar")),
    T_ARI (jerry_create_string ((const jerry_char_t *) "foo"), jerry_create_undefined ()),
    T_ARI (jerry_create_string ((const jerry_char_t *) "foo"), jerry_create_null ()),
    T_ARI (jerry_create_string ((const jerry_char_t *) "foo"), jerry_create_number (5.0)),
    T_ARI (jerry_create_undefined (), jerry_create_string ((const jerry_char_t *) "foo")),
    T_ARI (jerry_create_null (), jerry_create_string ((const jerry_char_t *) "foo")),
    T_ARI (jerry_create_number (5.0), jerry_create_string ((const jerry_char_t *) "foo")),
    T_ARI (jerry_create_undefined (), jerry_create_undefined ()),
    T_ARI (jerry_create_undefined (), jerry_create_null ()),
    T_ARI (jerry_create_null (), jerry_create_undefined ()),
    T_ARI (jerry_acquire_value (obj1), jerry_acquire_value (obj1)),
    T_ARI (jerry_acquire_value (obj1), jerry_acquire_value (obj2)),
    T_ARI (jerry_acquire_value (obj2), jerry_acquire_value (obj1)),
    T_ARI (jerry_acquire_value (obj2), jerry_create_undefined ()),
    T_ARI (jerry_acquire_value (obj1), jerry_create_string ((const jerry_char_t *) "foo")),
    T_ARI (jerry_acquire_value (obj1), jerry_create_null ()),
    T_ARI (jerry_acquire_value (obj1), jerry_create_boolean (true)),
    T_ARI (jerry_acquire_value (obj1), jerry_create_boolean (false)),
    T_ARI (jerry_acquire_value (obj1), jerry_create_number (5.0)),

    /* Testing division (/) */
    T_NAN (JERRY_BIN_OP_DIV, jerry_create_boolean (false), jerry_create_boolean (false)),
    T_NAN (JERRY_BIN_OP_DIV, jerry_create_number (0.0), jerry_create_number (0.0)),
    T_NAN (JERRY_BIN_OP_DIV, jerry_create_null (), jerry_create_null ()),

    /* Testing remainder (%) */
    T_NAN (JERRY_BIN_OP_REM, jerry_create_boolean (true), jerry_create_boolean (false)),
    T_NAN (JERRY_BIN_OP_REM, jerry_create_boolean (false), jerry_create_boolean (false)),
    T_NAN (JERRY_BIN_OP_REM, jerry_create_number (0.0), jerry_create_number (0.0)),
    T_NAN (JERRY_BIN_OP_REM, jerry_create_null (), jerry_create_null ()),
  };

  for (uint32_t idx = 0; idx < sizeof (test_nans) / sizeof (test_nan_entry_t); idx++)
  {
    jerry_value_t result = jerry_binary_operation (test_nans[idx].op, test_nans[idx].lhs, test_nans[idx].rhs);
    TEST_ASSERT (jerry_value_is_number (result));

    double num = jerry_get_number_value (result);

    TEST_ASSERT (num != num);

    jerry_release_value (test_nans[idx].lhs);
    jerry_release_value (test_nans[idx].rhs);
    jerry_release_value (result);
  }

  test_entry_t tests[] =
  {
    /* Testing addition (+) */
    T (JERRY_BIN_OP_ADD, jerry_create_number (5.0), jerry_create_number (5.0), jerry_create_number (10.0)),
    T (JERRY_BIN_OP_ADD, jerry_create_number (3.1), jerry_create_number (10), jerry_create_number (13.1)),
    T (JERRY_BIN_OP_ADD, jerry_create_number (3.1), jerry_create_boolean (true), jerry_create_number (4.1)),
    T (JERRY_BIN_OP_ADD,
       jerry_create_string ((const jerry_char_t *) "foo"),
       jerry_create_string ((const jerry_char_t *) "bar"),
       jerry_create_string ((const jerry_char_t *) "foobar")),
    T (JERRY_BIN_OP_ADD,
       jerry_create_string ((const jerry_char_t *) "foo"),
       jerry_create_undefined (),
       jerry_create_string ((const jerry_char_t *) "fooundefined")),
    T (JERRY_BIN_OP_ADD,
       jerry_create_string ((const jerry_char_t *) "foo"),
       jerry_create_null (),
       jerry_create_string ((const jerry_char_t *) "foonull")),
    T (JERRY_BIN_OP_ADD,
       jerry_create_string ((const jerry_char_t *) "foo"),
       jerry_create_number (5.0),
       jerry_create_string ((const jerry_char_t *) "foo5")),

    T (JERRY_BIN_OP_ADD, jerry_create_null (), jerry_create_null (), jerry_create_number (0.0)),
    T (JERRY_BIN_OP_ADD, jerry_create_boolean (true), jerry_create_boolean (true), jerry_create_number (2.0)),
    T (JERRY_BIN_OP_ADD, jerry_create_boolean (true), jerry_create_boolean (false), jerry_create_number (1.0)),
    T (JERRY_BIN_OP_ADD, jerry_create_boolean (false), jerry_create_boolean (true), jerry_create_number (1.0)),
    T (JERRY_BIN_OP_ADD, jerry_create_boolean (false), jerry_create_boolean (false), jerry_create_number (0.0)),
    T (JERRY_BIN_OP_ADD,
       jerry_acquire_value (obj1),
       jerry_acquire_value (obj1),
       jerry_create_string ((const jerry_char_t *) "[object Object][object Object]")),
    T (JERRY_BIN_OP_ADD,
       jerry_acquire_value (obj1),
       jerry_acquire_value (obj2),
       jerry_create_string ((const jerry_char_t *) "[object Object][object Object]")),
    T (JERRY_BIN_OP_ADD,
       jerry_acquire_value (obj2),
       jerry_acquire_value (obj1),
       jerry_create_string ((const jerry_char_t *) "[object Object][object Object]")),
    T (JERRY_BIN_OP_ADD,
       jerry_acquire_value (obj1),
       jerry_create_null (),
       jerry_create_string ((const jerry_char_t *) "[object Object]null")),
    T (JERRY_BIN_OP_ADD,
       jerry_acquire_value (obj1),
       jerry_create_undefined (),
       jerry_create_string ((const jerry_char_t *) "[object Object]undefined")),
    T (JERRY_BIN_OP_ADD,
       jerry_acquire_value (obj1),
       jerry_create_boolean (true),
       jerry_create_string ((const jerry_char_t *) "[object Object]true")),
    T (JERRY_BIN_OP_ADD,
       jerry_acquire_value (obj1),
       jerry_create_boolean (false),
       jerry_create_string ((const jerry_char_t *) "[object Object]false")),
    T (JERRY_BIN_OP_ADD,
       jerry_acquire_value (obj1),
       jerry_create_number (5.0),
       jerry_create_string ((const jerry_char_t *) "[object Object]5")),
    T (JERRY_BIN_OP_ADD,
       jerry_acquire_value (obj1),
       jerry_create_string ((const jerry_char_t *) "foo"),
       jerry_create_string ((const jerry_char_t *) "[object Object]foo")),

    /* Testing subtraction (-) */
    T (JERRY_BIN_OP_SUB, jerry_create_number (5.0), jerry_create_number (5.0), jerry_create_number (0.0)),
    T (JERRY_BIN_OP_SUB, jerry_create_number (3.1), jerry_create_number (10), jerry_create_number (-6.9)),
    T (JERRY_BIN_OP_SUB, jerry_create_number (3.1), jerry_create_boolean (true), jerry_create_number (2.1)),
    T (JERRY_BIN_OP_SUB, jerry_create_boolean (true), jerry_create_boolean (true), jerry_create_number (0.0)),
    T (JERRY_BIN_OP_SUB, jerry_create_boolean (true), jerry_create_boolean (false), jerry_create_number (1.0)),
    T (JERRY_BIN_OP_SUB, jerry_create_boolean (false), jerry_create_boolean (true), jerry_create_number (-1.0)),
    T (JERRY_BIN_OP_SUB, jerry_create_boolean (false), jerry_create_boolean (false), jerry_create_number (0.0)),
    T (JERRY_BIN_OP_SUB, jerry_create_null (), jerry_create_null (), jerry_create_number (-0.0)),


    /* Testing multiplication (*) */
    T (JERRY_BIN_OP_MUL, jerry_create_number (5.0), jerry_create_number (5.0), jerry_create_number (25.0)),
    T (JERRY_BIN_OP_MUL, jerry_create_number (3.1), jerry_create_number (10), jerry_create_number (31)),
    T (JERRY_BIN_OP_MUL, jerry_create_number (3.1), jerry_create_boolean (true), jerry_create_number (3.1)),
    T (JERRY_BIN_OP_MUL, jerry_create_boolean (true), jerry_create_boolean (true), jerry_create_number (1.0)),
    T (JERRY_BIN_OP_MUL, jerry_create_boolean (true), jerry_create_boolean (false), jerry_create_number (0.0)),
    T (JERRY_BIN_OP_MUL, jerry_create_boolean (false), jerry_create_boolean (true), jerry_create_number (0.0)),
    T (JERRY_BIN_OP_MUL, jerry_create_boolean (false), jerry_create_boolean (false), jerry_create_number (0.0)),
    T (JERRY_BIN_OP_MUL, jerry_create_null (), jerry_create_null (), jerry_create_number (0.0)),

    /* Testing division (/) */
    T (JERRY_BIN_OP_DIV, jerry_create_number (5.0), jerry_create_number (5.0), jerry_create_number (1.0)),
    T (JERRY_BIN_OP_DIV, jerry_create_number (3.1), jerry_create_number (10), jerry_create_number (0.31)),
    T (JERRY_BIN_OP_DIV, jerry_create_number (3.1), jerry_create_boolean (true), jerry_create_number (3.1)),
    T (JERRY_BIN_OP_DIV, jerry_create_boolean (true), jerry_create_boolean (true), jerry_create_number (1.0)),
    T (JERRY_BIN_OP_DIV,
       jerry_create_boolean (true),
       jerry_create_boolean (false),
       jerry_create_number_infinity (false)),
    T (JERRY_BIN_OP_DIV, jerry_create_boolean (false), jerry_create_boolean (true), jerry_create_number (0.0)),

    /* Testing remainder (%) */
    T (JERRY_BIN_OP_REM, jerry_create_number (5.0), jerry_create_number (5.0), jerry_create_number (0.0)),
    T (JERRY_BIN_OP_REM, jerry_create_number (5.0), jerry_create_number (2.0), jerry_create_number (1.0)),
    T (JERRY_BIN_OP_REM, jerry_create_number (3.1), jerry_create_number (10), jerry_create_number (3.1)),
    T (JERRY_BIN_OP_REM,
       jerry_create_number (3.1),
       jerry_create_boolean (true),
       jerry_create_number (0.10000000000000009)),
    T (JERRY_BIN_OP_REM, jerry_create_boolean (true), jerry_create_boolean (true), jerry_create_number (0.0)),
    T (JERRY_BIN_OP_REM, jerry_create_boolean (false), jerry_create_boolean (true), jerry_create_number (0.0)),

  };

  for (uint32_t idx = 0; idx < sizeof (tests) / sizeof (test_entry_t); idx++)
  {
    jerry_value_t result = jerry_binary_operation (tests[idx].op, tests[idx].lhs, tests[idx].rhs);
    TEST_ASSERT (!jerry_value_is_error (result));

    jerry_value_t equals = jerry_binary_operation (JERRY_BIN_OP_STRICT_EQUAL, result, tests[idx].expected);
    TEST_ASSERT (jerry_value_is_boolean (equals) && jerry_get_boolean_value (equals));
    jerry_release_value (equals);

    jerry_release_value (tests[idx].lhs);
    jerry_release_value (tests[idx].rhs);
    jerry_release_value (tests[idx].expected);
    jerry_release_value (result);
  }

  jerry_value_t obj3 = jerry_eval ((const jerry_char_t *) "o={valueOf:function(){throw 5}};o", 33, JERRY_PARSE_NO_OPTS);

  test_error_entry_t error_tests[] =
  {
    /* Testing addition (+) */
    T_ERR (JERRY_BIN_OP_ADD, jerry_acquire_value (err1), jerry_acquire_value (err1)),
    T_ERR (JERRY_BIN_OP_ADD, jerry_acquire_value (err1), jerry_create_undefined ()),
    T_ERR (JERRY_BIN_OP_ADD, jerry_create_undefined (), jerry_acquire_value (err1)),

    /* Testing subtraction (-), multiplication (*), division (/), remainder (%) */
    T_ARI (jerry_acquire_value (err1), jerry_acquire_value (err1)),
    T_ARI (jerry_acquire_value (err1), jerry_create_undefined ()),
    T_ARI (jerry_create_undefined (), jerry_acquire_value (err1)),

    /* Testing addition (+) */
    T_ERR (JERRY_BIN_OP_ADD, jerry_acquire_value (obj3), jerry_create_undefined ()),
    T_ERR (JERRY_BIN_OP_ADD, jerry_acquire_value (obj3), jerry_create_null ()),
    T_ERR (JERRY_BIN_OP_ADD, jerry_acquire_value (obj3), jerry_create_boolean (true)),
    T_ERR (JERRY_BIN_OP_ADD, jerry_acquire_value (obj3), jerry_create_boolean (false)),
    T_ERR (JERRY_BIN_OP_ADD, jerry_acquire_value (obj3), jerry_acquire_value (obj2)),
    T_ERR (JERRY_BIN_OP_ADD, jerry_acquire_value (obj3), jerry_create_string ((const jerry_char_t *) "foo")),

    /* Testing subtraction (-), multiplication (*), division (/), remainder (%) */
    T_ARI (jerry_acquire_value (obj3), jerry_create_undefined ()),
    T_ARI (jerry_acquire_value (obj3), jerry_create_null ()),
    T_ARI (jerry_acquire_value (obj3), jerry_create_boolean (true)),
    T_ARI (jerry_acquire_value (obj3), jerry_create_boolean (false)),
    T_ARI (jerry_acquire_value (obj3), jerry_acquire_value (obj2)),
    T_ARI (jerry_acquire_value (obj3), jerry_create_string ((const jerry_char_t *) "foo")),
  };

  for (uint32_t idx = 0; idx < sizeof (error_tests) / sizeof (test_error_entry_t); idx++)
  {
    jerry_value_t result = jerry_binary_operation (tests[idx].op, error_tests[idx].lhs, error_tests[idx].rhs);
    TEST_ASSERT (jerry_value_is_error (result));
    jerry_release_value (error_tests[idx].lhs);
    jerry_release_value (error_tests[idx].rhs);
    jerry_release_value (result);
  }

  jerry_release_value (obj1);
  jerry_release_value (obj2);
  jerry_release_value (obj3);
  jerry_release_value (err1);

  jerry_cleanup ();

  return 0;
}