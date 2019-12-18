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
typedef  int /*<<< orphan*/  (* jerryx_arg_transform_func_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ;
typedef  int /*<<< orphan*/  jerryx_arg_t ;
typedef  int /*<<< orphan*/  jerryx_arg_js_iterator_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;

/* Variables and functions */
 scalar_t__ jerry_value_is_undefined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_arg_js_iterator_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jerryx_arg_js_iterator_pop (int /*<<< orphan*/ *) ; 

jerry_value_t
jerryx_arg_transform_optional (jerryx_arg_js_iterator_t *js_arg_iter_p, /**< available JS args */
                               const jerryx_arg_t *c_arg_p, /**< native arg */
                               jerryx_arg_transform_func_t func) /**< the core transform function */
{
  jerry_value_t js_arg = jerryx_arg_js_iterator_peek (js_arg_iter_p);

  if (jerry_value_is_undefined (js_arg))
  {
    return jerryx_arg_js_iterator_pop (js_arg_iter_p);
  }

  return func (js_arg_iter_p, c_arg_p);
}