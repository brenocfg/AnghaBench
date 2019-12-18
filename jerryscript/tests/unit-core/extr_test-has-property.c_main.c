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
 int /*<<< orphan*/  TEST_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_INIT () ; 
 int /*<<< orphan*/  assert_boolean_and_release (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jerry_cleanup () ; 
 int /*<<< orphan*/  jerry_create_boolean (int) ; 
 int /*<<< orphan*/  jerry_create_object () ; 
 int /*<<< orphan*/  jerry_create_string_from_utf8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jerry_delete_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_has_own_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_has_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_set_prototype (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
main (void)
{
  TEST_INIT ();

  jerry_init (JERRY_INIT_EMPTY);

  jerry_value_t object = jerry_create_object ();
  jerry_value_t prop_name = jerry_create_string_from_utf8 ((jerry_char_t *) "something");
  jerry_value_t prop_value = jerry_create_boolean (true);
  jerry_value_t proto_object = jerry_create_object ();

  /* Assert that an empty object does not have the property in question */
  assert_boolean_and_release (jerry_has_property (object, prop_name), false);
  assert_boolean_and_release (jerry_has_own_property (object, prop_name), false);

  assert_boolean_and_release (jerry_set_prototype (object, proto_object), true);

  /* If the object has a prototype, that still means it doesn't have the property */
  assert_boolean_and_release (jerry_has_property (object, prop_name), false);
  assert_boolean_and_release (jerry_has_own_property (object, prop_name), false);

  assert_boolean_and_release (jerry_set_property (proto_object, prop_name, prop_value), true);

  /* After setting the property on the prototype, it must be there, but not on the object */
  assert_boolean_and_release (jerry_has_property (object, prop_name), true);
  assert_boolean_and_release (jerry_has_own_property (object, prop_name), false);

  TEST_ASSERT (jerry_delete_property (proto_object, prop_name));
  assert_boolean_and_release (jerry_set_property (object, prop_name, prop_value), true);

  /* After relocating the property onto the object, it must be there */
  assert_boolean_and_release (jerry_has_property (object, prop_name), true);
  assert_boolean_and_release (jerry_has_own_property (object, prop_name), true);

  jerry_release_value (object);
  jerry_release_value (prop_name);
  jerry_release_value (prop_value);
  jerry_release_value (proto_object);

  jerry_cleanup ();

  return 0;
}