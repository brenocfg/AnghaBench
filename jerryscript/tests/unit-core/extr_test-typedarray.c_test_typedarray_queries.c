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
typedef  size_t uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  bytes_per_element; int /*<<< orphan*/  element_count; int /*<<< orphan*/  typedarray_type; int /*<<< orphan*/ * constructor_name; } ;
typedef  TYPE_1__ test_entry_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  jerry_construct_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jerry_create_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_create_string (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  jerry_create_typedarray (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_get_global_object () ; 
 int /*<<< orphan*/  jerry_get_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_typedarray_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_typedarray_queries (test_entry_t test_entries[]) /**< test cases */
{
  jerry_value_t global_obj_val = jerry_get_global_object ();

  for (uint32_t i = 0; test_entries[i].constructor_name != NULL; i++)
  {
    /* Create TypedArray via construct call */
    {
      jerry_value_t prop_name = jerry_create_string ((const jerry_char_t *) test_entries[i].constructor_name);
      jerry_value_t prop_value = jerry_get_property (global_obj_val, prop_name);
      TEST_ASSERT (!jerry_value_is_error (prop_value));
      jerry_value_t length_arg = jerry_create_number (test_entries[i].element_count);

      jerry_value_t typedarray = jerry_construct_object (prop_value, &length_arg, 1);

      jerry_release_value (prop_name);
      jerry_release_value (prop_value);
      jerry_release_value (length_arg);

      test_typedarray_info (typedarray,
                            test_entries[i].typedarray_type,
                            test_entries[i].element_count,
                            test_entries[i].bytes_per_element);
      jerry_release_value (typedarray);
    }

    /* Create TypedArray via api call */
    {
      jerry_value_t typedarray = jerry_create_typedarray (test_entries[i].typedarray_type,
                                                          test_entries[i].element_count);
      test_typedarray_info (typedarray,
                            test_entries[i].typedarray_type,
                            test_entries[i].element_count,
                            test_entries[i].bytes_per_element);
      jerry_release_value (typedarray);
    }
  }

  jerry_release_value (global_obj_val);
}