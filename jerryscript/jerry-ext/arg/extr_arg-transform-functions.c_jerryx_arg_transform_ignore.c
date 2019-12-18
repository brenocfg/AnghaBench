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

/* Variables and functions */
 int /*<<< orphan*/  jerry_create_undefined () ; 

jerry_value_t
jerryx_arg_transform_ignore (jerryx_arg_js_iterator_t *js_arg_iter_p, /**< available JS args */
                             const jerryx_arg_t *c_arg_p) /**< the native arg */
{
  (void) js_arg_iter_p; /* unused */
  (void) c_arg_p; /* unused */

  return jerry_create_undefined ();
}