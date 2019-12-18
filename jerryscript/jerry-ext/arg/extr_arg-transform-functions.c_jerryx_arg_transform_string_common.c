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
typedef  int /*<<< orphan*/  jerryx_arg_t ;
typedef  int /*<<< orphan*/  jerryx_arg_js_iterator_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_ERROR_TYPE ; 
 int /*<<< orphan*/  jerry_create_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_value_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_arg_js_iterator_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jerryx_arg_string_to_buffer_common_routine (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static jerry_value_t
jerryx_arg_transform_string_common (jerryx_arg_js_iterator_t *js_arg_iter_p, /**< available JS args */
                                    const jerryx_arg_t *c_arg_p, /**< the native arg */
                                    bool is_utf8) /**< whether it is a UTF-8 string */
{
  jerry_value_t js_arg = jerryx_arg_js_iterator_pop (js_arg_iter_p);

  jerry_value_t to_string = jerry_value_to_string (js_arg);

  if (jerry_value_is_error (to_string))
  {
    jerry_release_value (to_string);

    return jerry_create_error (JERRY_ERROR_TYPE,
                               (jerry_char_t *) "It can not be converted to a string.");
  }

  jerry_value_t ret = jerryx_arg_string_to_buffer_common_routine (to_string, c_arg_p, is_utf8);
  jerry_release_value (to_string);

  return ret;
}