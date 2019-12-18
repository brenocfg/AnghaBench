#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jerry_value_t ;
struct TYPE_5__ {int is_configurable_defined; int is_configurable; } ;
typedef  TYPE_1__ jerry_property_descriptor_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_create_string (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  jerry_define_own_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  jerry_free_property_descriptor_fields (TYPE_1__*) ; 
 int /*<<< orphan*/  jerry_init_property_descriptor_fields (TYPE_1__*) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_value_is_boolean (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
freeze_property (jerry_value_t target_obj, /**< target object */
                 const char *target_prop) /**< target property name */
{
  // "freeze" property
  jerry_property_descriptor_t prop_desc;
  jerry_init_property_descriptor_fields (&prop_desc);
  prop_desc.is_configurable_defined = true;
  prop_desc.is_configurable = false;

  jerry_value_t prop_name = jerry_create_string ((const jerry_char_t *) target_prop);
  jerry_value_t return_value = jerry_define_own_property (target_obj, prop_name, &prop_desc);
  TEST_ASSERT (jerry_value_is_boolean (return_value));
  jerry_release_value (return_value);
  jerry_release_value (prop_name);

  jerry_free_property_descriptor_fields (&prop_desc);
}