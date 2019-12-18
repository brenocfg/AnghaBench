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
typedef  int /*<<< orphan*/  jerry_error_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  jerry_create_error (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  jerry_create_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_get_value_from_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  module_name_property_name ; 

__attribute__((used)) static jerry_value_t
jerryx_module_create_error (jerry_error_t error_type, /**< the type of error to create */
                            const jerry_char_t *message, /**< the error message */
                            const jerry_value_t module_name) /**< the module name */
{
  jerry_value_t ret = jerry_create_error (error_type, message);

  jerry_value_t error_object = jerry_get_value_from_error (ret, false);
  jerry_value_t property_name = jerry_create_string (module_name_property_name);

  jerry_release_value (jerry_set_property (error_object, property_name, module_name));

  jerry_release_value (property_name);
  jerry_release_value (error_object);
  return ret;
}