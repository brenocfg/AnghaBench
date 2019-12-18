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
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  scalar_t__ jerry_length_t ;
typedef  int /*<<< orphan*/  jerry_gc_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_GC_PRESSURE_HIGH ; 
 int /*<<< orphan*/  JERRY_GC_PRESSURE_LOW ; 
 int /*<<< orphan*/  jerry_create_undefined () ; 
 int /*<<< orphan*/  jerry_gc (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_value_to_boolean (int /*<<< orphan*/  const) ; 

jerry_value_t
jerryx_handler_gc (const jerry_value_t func_obj_val, /**< function object */
                   const jerry_value_t this_p, /**< this arg */
                   const jerry_value_t args_p[], /**< function arguments */
                   const jerry_length_t args_cnt) /**< number of function arguments */
{
  (void) func_obj_val; /* unused */
  (void) this_p; /* unused */

  jerry_gc_mode_t mode = ((args_cnt > 0 && jerry_value_to_boolean (args_p[0])) ? JERRY_GC_PRESSURE_HIGH
                                                                               : JERRY_GC_PRESSURE_LOW);

  jerry_gc (mode);
  return jerry_create_undefined ();
}