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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  jerryx_register_result ;
struct TYPE_3__ {int /*<<< orphan*/  value; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ jerryx_property_entry ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRYX_SET_PROPERTIES_RESULT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jerry_create_string_from_utf8 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  jerry_create_undefined () ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_set_property (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_value_is_boolean (int /*<<< orphan*/ ) ; 

jerryx_register_result
jerryx_set_properties (const jerry_value_t target_object, /**< target object */
                       const jerryx_property_entry entries[]) /**< array of method entries */
{
#define JERRYX_SET_PROPERTIES_RESULT(VALUE, IDX) ((jerryx_register_result) { VALUE, IDX })
  uint32_t idx = 0;
  for (; ((entries + idx) != NULL) && (entries[idx].name != NULL); idx++)
  {
    const jerryx_property_entry *entry = &entries[idx];

    jerry_value_t prop_name = jerry_create_string_from_utf8 ((const jerry_char_t *) entry->name);
    jerry_value_t result = jerry_set_property (target_object, prop_name, entry->value);

    jerry_release_value (prop_name);

    // By API definition:
    // The jerry_set_property returns TRUE if there is no problem
    // and error object if there is any problem.
    // Thus there is no need to check if the boolean value is false or not.
    if (!jerry_value_is_boolean (result))
    {
      return JERRYX_SET_PROPERTIES_RESULT (result, idx);
    }

    jerry_release_value (entry->value);
    jerry_release_value (result);
  }

  return JERRYX_SET_PROPERTIES_RESULT (jerry_create_undefined (), idx);
#undef JERRYX_SET_PROPERTIES_RESULT
}