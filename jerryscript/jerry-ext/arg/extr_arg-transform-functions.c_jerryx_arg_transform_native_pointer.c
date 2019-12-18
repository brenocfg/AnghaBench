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
struct TYPE_3__ {scalar_t__ dest; scalar_t__ extra_info; } ;
typedef  TYPE_1__ jerryx_arg_t ;
typedef  int /*<<< orphan*/  jerryx_arg_js_iterator_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  int /*<<< orphan*/  jerry_object_native_info_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_ERROR_TYPE ; 
 int /*<<< orphan*/  jerry_create_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jerry_create_undefined () ; 
 int jerry_get_object_native_pointer (int /*<<< orphan*/ ,void**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  jerry_value_is_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_arg_js_iterator_pop (int /*<<< orphan*/ *) ; 

jerry_value_t
jerryx_arg_transform_native_pointer (jerryx_arg_js_iterator_t *js_arg_iter_p, /**< available JS args */
                                     const jerryx_arg_t *c_arg_p) /**< the native arg */
{
  jerry_value_t js_arg = jerryx_arg_js_iterator_pop (js_arg_iter_p);

  if (!jerry_value_is_object (js_arg))
  {
    return jerry_create_error (JERRY_ERROR_TYPE,
                               (jerry_char_t *) "It is not an object.");
  }

  const jerry_object_native_info_t *expected_info_p;
  expected_info_p = (const jerry_object_native_info_t *) c_arg_p->extra_info;
  void **ptr_p = (void **) c_arg_p->dest;
  bool is_ok = jerry_get_object_native_pointer (js_arg, ptr_p, expected_info_p);

  if (!is_ok)
  {
    return jerry_create_error (JERRY_ERROR_TYPE,
                               (jerry_char_t *) "The object has no native pointer or type does not match.");
  }

  return jerry_create_undefined ();
}