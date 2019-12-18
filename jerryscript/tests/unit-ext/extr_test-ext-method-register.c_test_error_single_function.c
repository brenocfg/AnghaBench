#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ registered; int /*<<< orphan*/  result; } ;
typedef  TYPE_1__ jerryx_register_result ;
typedef  int /*<<< orphan*/  jerryx_property_entry ;
typedef  int /*<<< orphan*/  jerry_value_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRYX_PROPERTY_FUNCTION (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JERRYX_PROPERTY_LIST_END () ; 
 int /*<<< orphan*/  JERRY_INIT_EMPTY ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  freeze_property (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  jerry_cleanup () ; 
 int /*<<< orphan*/  jerry_create_object () ; 
 int /*<<< orphan*/  jerry_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_release_property_entry (int /*<<< orphan*/ *,TYPE_1__) ; 
 TYPE_1__ jerryx_set_properties (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  method_hello ; 

__attribute__((used)) static void
test_error_single_function (void)
{
  jerry_init (JERRY_INIT_EMPTY);

  const char *target_prop = "test_err";
  jerry_value_t target_object = jerry_create_object ();
  freeze_property (target_object, target_prop);

  jerryx_property_entry methods[] =
  {
    JERRYX_PROPERTY_FUNCTION (target_prop, method_hello), // This registration should fail
    JERRYX_PROPERTY_LIST_END (),
  };

  jerryx_register_result register_result = jerryx_set_properties (target_object, methods);

  TEST_ASSERT (register_result.registered == 0);
  TEST_ASSERT (jerry_value_is_error (register_result.result));
  jerryx_release_property_entry (methods, register_result);
  jerry_release_value (register_result.result);

  jerry_release_value (target_object);

  jerry_cleanup ();
}