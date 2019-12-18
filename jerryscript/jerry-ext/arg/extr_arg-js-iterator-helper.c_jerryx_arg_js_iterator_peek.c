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
struct TYPE_3__ {scalar_t__ js_arg_idx; scalar_t__ js_arg_cnt; int /*<<< orphan*/ * js_arg_p; } ;
typedef  TYPE_1__ jerryx_arg_js_iterator_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;

/* Variables and functions */
 int /*<<< orphan*/  jerry_create_undefined () ; 

jerry_value_t
jerryx_arg_js_iterator_peek (jerryx_arg_js_iterator_t *js_arg_iter_p) /**< the JS arg iterator */
{
  return (js_arg_iter_p->js_arg_idx < js_arg_iter_p->js_arg_cnt ? *js_arg_iter_p->js_arg_p
                                                                : jerry_create_undefined ());
}