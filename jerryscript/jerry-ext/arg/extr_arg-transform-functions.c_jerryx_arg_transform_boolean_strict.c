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
struct TYPE_3__ {int* dest; } ;
typedef  TYPE_1__ jerryx_arg_t ;
typedef  int /*<<< orphan*/  jerryx_arg_js_iterator_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_ERROR_TYPE ; 
 int /*<<< orphan*/  jerry_create_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jerry_create_undefined () ; 
 int jerry_get_boolean_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_value_is_boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_arg_js_iterator_pop (int /*<<< orphan*/ *) ; 

jerry_value_t
jerryx_arg_transform_boolean_strict (jerryx_arg_js_iterator_t *js_arg_iter_p, /**< available JS args */
                                     const jerryx_arg_t *c_arg_p) /**< the native arg */
{
  jerry_value_t js_arg = jerryx_arg_js_iterator_pop (js_arg_iter_p);

  if (!jerry_value_is_boolean (js_arg))
  {
    return jerry_create_error (JERRY_ERROR_TYPE,
                               (jerry_char_t *) "It is not a boolean.");
  }

  bool *dest = c_arg_p->dest;
  *dest = jerry_get_boolean_value (js_arg);

  return jerry_create_undefined ();
}