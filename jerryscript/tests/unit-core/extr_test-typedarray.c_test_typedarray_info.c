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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  scalar_t__ jerry_typedarray_type_t ;
typedef  scalar_t__ jerry_length_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  jerry_get_typedarray_buffer (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 scalar_t__ jerry_get_typedarray_length (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_get_typedarray_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int jerry_value_is_arraybuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int jerry_value_is_typedarray (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_typedarray_info (jerry_value_t typedarray, /**< target TypedArray to query */
                      jerry_typedarray_type_t typedarray_type, /**< expected TypedArray type */
                      jerry_length_t element_count, /**< expected element count */
                      jerry_length_t bytes_per_element) /**< bytes per element for the given type */
{
  TEST_ASSERT (!jerry_value_is_error (typedarray));
  TEST_ASSERT (jerry_value_is_typedarray (typedarray));
  TEST_ASSERT (jerry_get_typedarray_type (typedarray) == typedarray_type);
  TEST_ASSERT (jerry_get_typedarray_length (typedarray) == element_count);

  jerry_length_t byte_length = (uint32_t) -1;
  jerry_length_t byte_offset = (uint32_t) -1;
  jerry_value_t arraybuffer = jerry_get_typedarray_buffer (typedarray, &byte_offset, &byte_length);
  TEST_ASSERT (jerry_value_is_arraybuffer (arraybuffer));

  TEST_ASSERT (byte_length == element_count * bytes_per_element);
  TEST_ASSERT (byte_offset == 0);

  jerry_release_value (arraybuffer);
}