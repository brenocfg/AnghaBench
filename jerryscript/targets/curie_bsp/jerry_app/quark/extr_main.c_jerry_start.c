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
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_INIT_EMPTY ; 
 int /*<<< orphan*/  jerry_create_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jerry_get_global_object () ; 
 int /*<<< orphan*/  jerry_get_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_init (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_port_get_current_time () ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_function ; 
 int /*<<< orphan*/  srand (unsigned int) ; 

void jerry_start ()
{
  srand ((unsigned) jerry_port_get_current_time ());
  jerry_init (JERRY_INIT_EMPTY);
  jerry_value_t global_obj_val = jerry_get_global_object ();
  jerry_value_t print_func_name_val = jerry_create_string ((jerry_char_t *) "print");
  print_function = jerry_get_property (global_obj_val, print_func_name_val);
  jerry_release_value (print_func_name_val);
  jerry_release_value (global_obj_val);
}