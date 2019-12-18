#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ extra_info; } ;
typedef  TYPE_1__ jerryx_arg_t ;
typedef  int /*<<< orphan*/  jerryx_arg_js_iterator_t ;
struct TYPE_5__ {int /*<<< orphan*/  c_arg_cnt; int /*<<< orphan*/  c_arg_p; } ;
typedef  TYPE_2__ jerryx_arg_array_items_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;

/* Variables and functions */
 int /*<<< orphan*/  jerryx_arg_js_iterator_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jerryx_arg_transform_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

jerry_value_t
jerryx_arg_transform_array_items (jerryx_arg_js_iterator_t *js_arg_iter_p, /**< available JS args */
                                  const jerryx_arg_t *c_arg_p) /**< the native arg */
{
  jerry_value_t js_arg = jerryx_arg_js_iterator_pop (js_arg_iter_p);

  const jerryx_arg_array_items_t *array_items_p = (const jerryx_arg_array_items_t *) c_arg_p->extra_info;

  return jerryx_arg_transform_array (js_arg,
                                     array_items_p->c_arg_p,
                                     array_items_p->c_arg_cnt);
}