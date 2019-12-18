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

/* Variables and functions */
 int /*<<< orphan*/  JERRY_INIT_EMPTY ; 
 int /*<<< orphan*/  TEST_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeze_property (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  jerry_cleanup () ; 
 int /*<<< orphan*/  jerry_create_object () ; 
 int /*<<< orphan*/  jerry_get_global_object () ; 
 int /*<<< orphan*/  jerry_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_set_property_str (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_error_setvalue (void)
{
  jerry_init (JERRY_INIT_EMPTY);

  const char *target_prop = "test_err";
  jerry_value_t global_obj = jerry_get_global_object ();
  freeze_property (global_obj, target_prop);

  jerry_value_t new_object = jerry_create_object ();
  jerry_value_t set_result = jerryx_set_property_str (global_obj, target_prop, new_object);
  TEST_ASSERT (jerry_value_is_error (set_result));

  jerry_release_value (set_result);
  jerry_release_value (new_object);
  jerry_release_value (global_obj);

  jerry_cleanup ();
}