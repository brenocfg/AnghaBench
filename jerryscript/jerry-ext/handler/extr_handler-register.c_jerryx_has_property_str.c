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
 int /*<<< orphan*/  jerry_create_string_from_utf8 (int /*<<< orphan*/  const*) ; 
 int jerry_get_boolean_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_has_property (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_value_is_error (int /*<<< orphan*/ ) ; 

bool
jerryx_has_property_str (const jerry_value_t target_object, /**< target object */
                         const char *name) /**< property name */
{
  bool has_property = false;

  jerry_value_t prop_name = jerry_create_string_from_utf8 ((const jerry_char_t *) name);
  jerry_value_t has_prop_val = jerry_has_property (target_object, prop_name);

  if (!jerry_value_is_error (has_prop_val))
  {
    has_property = jerry_get_boolean_value (has_prop_val);
  }

  jerry_release_value (has_prop_val);
  jerry_release_value (prop_name);

  return has_property;
}