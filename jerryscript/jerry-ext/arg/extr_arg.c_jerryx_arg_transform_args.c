#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* func ) (TYPE_2__*,TYPE_1__ const*) ;} ;
typedef  TYPE_1__ jerryx_arg_t ;
struct TYPE_7__ {scalar_t__ const js_arg_cnt; int /*<<< orphan*/  js_arg_idx; int /*<<< orphan*/  const* js_arg_p; } ;
typedef  TYPE_2__ jerryx_arg_js_iterator_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  scalar_t__ jerry_length_t ;

/* Variables and functions */
 int /*<<< orphan*/  jerry_create_undefined () ; 
 int /*<<< orphan*/  jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_1__ const*) ; 

jerry_value_t
jerryx_arg_transform_args (const jerry_value_t *js_arg_p, /**< points to the array with JS arguments */
                           const jerry_length_t js_arg_cnt, /**< the count of the `js_arg_p` array */
                           const jerryx_arg_t *c_arg_p, /**< points to the array of validation/transformation steps */
                           jerry_length_t c_arg_cnt) /**< the count of the `c_arg_p` array */
{
  jerry_value_t ret = jerry_create_undefined ();

  jerryx_arg_js_iterator_t iterator =
  {
    .js_arg_p = js_arg_p,
    .js_arg_cnt = js_arg_cnt,
    .js_arg_idx = 0
  };

  for (; c_arg_cnt != 0 && !jerry_value_is_error (ret); c_arg_cnt--, c_arg_p++)
  {
    ret = c_arg_p->func (&iterator, c_arg_p);
  }

  return ret;
}