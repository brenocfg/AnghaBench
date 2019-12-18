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
typedef  int /*<<< orphan*/  jerryx_arg_js_iterator_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_ERROR_TYPE ; 
 int /*<<< orphan*/  jerry_create_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jerry_create_undefined () ; 
 double jerry_get_number_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_value_to_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_arg_js_iterator_pop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static jerry_value_t
jerryx_arg_transform_number_common (jerryx_arg_js_iterator_t *js_arg_iter_p, /**< available JS args */
                                    double *number_p) /**< [out] the number in JS arg */
{
  jerry_value_t js_arg = jerryx_arg_js_iterator_pop (js_arg_iter_p);

  jerry_value_t to_number = jerry_value_to_number (js_arg);

  if (jerry_value_is_error (to_number))
  {
    jerry_release_value (to_number);

    return jerry_create_error (JERRY_ERROR_TYPE,
                               (jerry_char_t *) "It can not be converted to a number.");
  }

  *number_p = jerry_get_number_value (to_number);
  jerry_release_value (to_number);

  return jerry_create_undefined ();
}