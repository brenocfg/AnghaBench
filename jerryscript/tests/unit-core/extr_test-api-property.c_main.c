#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jerry_value_t ;
struct TYPE_6__ {int is_value_defined; int is_writable_defined; int is_writable; int is_enumerable_defined; int is_enumerable; int is_configurable_defined; int is_configurable; int is_get_defined; int is_set_defined; int /*<<< orphan*/  setter; int /*<<< orphan*/  getter; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ jerry_property_descriptor_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_INIT_EMPTY ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_INIT () ; 
 int /*<<< orphan*/  jerry_acquire_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_cleanup () ; 
 int /*<<< orphan*/  jerry_create_string (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  jerry_define_own_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  jerry_free_property_descriptor_fields (TYPE_1__*) ; 
 int jerry_get_boolean_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_get_global_object () ; 
 int jerry_get_own_property_descriptor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  jerry_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_init_property_descriptor_fields (TYPE_1__*) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int jerry_value_is_boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int jerry_value_is_string (int /*<<< orphan*/ ) ; 
 int jerry_value_is_undefined (int /*<<< orphan*/ ) ; 

int
main (void)
{
  TEST_INIT ();

  jerry_init (JERRY_INIT_EMPTY);

  /* Test: init property descriptor */
  jerry_property_descriptor_t prop_desc;
  jerry_init_property_descriptor_fields (&prop_desc);
  TEST_ASSERT (prop_desc.is_value_defined == false);
  TEST_ASSERT (jerry_value_is_undefined (prop_desc.value));
  TEST_ASSERT (prop_desc.is_writable_defined == false);
  TEST_ASSERT (prop_desc.is_writable == false);
  TEST_ASSERT (prop_desc.is_enumerable_defined == false);
  TEST_ASSERT (prop_desc.is_enumerable == false);
  TEST_ASSERT (prop_desc.is_configurable_defined == false);
  TEST_ASSERT (prop_desc.is_configurable == false);
  TEST_ASSERT (prop_desc.is_get_defined == false);
  TEST_ASSERT (jerry_value_is_undefined (prop_desc.getter));
  TEST_ASSERT (prop_desc.is_set_defined == false);
  TEST_ASSERT (jerry_value_is_undefined (prop_desc.setter));

  /* Test: define own properties */
  jerry_value_t global_obj_val = jerry_get_global_object ();
  jerry_value_t prop_name = jerry_create_string ((const jerry_char_t *) "my_defined_property");
  prop_desc.is_value_defined = true;
  prop_desc.value = jerry_acquire_value (prop_name);
  jerry_value_t res = jerry_define_own_property (global_obj_val, prop_name, &prop_desc);
  TEST_ASSERT (!jerry_value_is_error (res));
  TEST_ASSERT (jerry_value_is_boolean (res));
  TEST_ASSERT (jerry_get_boolean_value (res));
  jerry_release_value (res);
  jerry_free_property_descriptor_fields (&prop_desc);

  /* Test: get own property descriptor */
  bool is_ok = jerry_get_own_property_descriptor (global_obj_val, prop_name, &prop_desc);
  TEST_ASSERT (is_ok);
  TEST_ASSERT (prop_desc.is_value_defined == true);
  TEST_ASSERT (jerry_value_is_string (prop_desc.value));
  TEST_ASSERT (prop_desc.is_writable == false);
  TEST_ASSERT (prop_desc.is_enumerable == false);
  TEST_ASSERT (prop_desc.is_configurable == false);
  TEST_ASSERT (prop_desc.is_get_defined == false);
  TEST_ASSERT (jerry_value_is_undefined (prop_desc.getter));
  TEST_ASSERT (prop_desc.is_set_defined == false);
  TEST_ASSERT (jerry_value_is_undefined (prop_desc.setter));
  jerry_release_value (prop_name);
  jerry_free_property_descriptor_fields (&prop_desc);

  jerry_release_value (global_obj_val);
  jerry_cleanup ();

  return 0;
}