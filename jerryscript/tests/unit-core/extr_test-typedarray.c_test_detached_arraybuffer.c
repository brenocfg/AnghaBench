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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  types ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  int /*<<< orphan*/  jerry_typedarray_type_t ;

/* Variables and functions */
 scalar_t__ JERRY_ERROR_TYPE ; 
#define  JERRY_TYPEDARRAY_FLOAT32 136 
#define  JERRY_TYPEDARRAY_FLOAT64 135 
#define  JERRY_TYPEDARRAY_INT16 134 
#define  JERRY_TYPEDARRAY_INT32 133 
#define  JERRY_TYPEDARRAY_INT8 132 
#define  JERRY_TYPEDARRAY_UINT16 131 
#define  JERRY_TYPEDARRAY_UINT32 130 
#define  JERRY_TYPEDARRAY_UINT8 129 
#define  JERRY_TYPEDARRAY_UINT8CLAMPED 128 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  jerry_create_arraybuffer_external (scalar_t__ const,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jerry_create_typedarray_for_arraybuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_create_typedarray_for_arraybuffer_sz (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jerry_detach_arraybuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ const jerry_get_arraybuffer_byte_length (int /*<<< orphan*/ ) ; 
 int jerry_get_boolean_value (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_get_error_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_is_arraybuffer_detachable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int jerry_value_is_arraybuffer (int /*<<< orphan*/ ) ; 
 int jerry_value_is_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_detached_arraybuffer (void)
{
  static jerry_typedarray_type_t types[] =
  {
    JERRY_TYPEDARRAY_UINT8,
    JERRY_TYPEDARRAY_UINT8CLAMPED,
    JERRY_TYPEDARRAY_INT8,
    JERRY_TYPEDARRAY_UINT16,
    JERRY_TYPEDARRAY_INT16,
    JERRY_TYPEDARRAY_UINT32,
    JERRY_TYPEDARRAY_INT32,
    JERRY_TYPEDARRAY_FLOAT32,
    JERRY_TYPEDARRAY_FLOAT64,
  };

  /* Creating an TypedArray for a detached array buffer with a given length/offset is invalid */
  {
    uint8_t buf[1];
    const uint32_t length = 1;
    jerry_value_t arraybuffer = jerry_create_arraybuffer_external (length, buf, NULL);
    TEST_ASSERT (!jerry_value_is_error (arraybuffer));
    TEST_ASSERT (jerry_value_is_arraybuffer (arraybuffer));
    TEST_ASSERT (jerry_get_arraybuffer_byte_length (arraybuffer) == length);

    jerry_value_t is_detachable = jerry_is_arraybuffer_detachable (arraybuffer);
    TEST_ASSERT (!jerry_value_is_error (is_detachable));
    TEST_ASSERT (jerry_get_boolean_value (is_detachable));
    jerry_release_value (is_detachable);

    jerry_value_t res = jerry_detach_arraybuffer (arraybuffer);
    TEST_ASSERT (!jerry_value_is_error (res));
    jerry_release_value (res);

    for (size_t idx = 0; idx < (sizeof (types) / sizeof (types[0])); idx++)
    {
      jerry_value_t typedarray = jerry_create_typedarray_for_arraybuffer_sz (types[idx], arraybuffer, 0, 4);
      TEST_ASSERT (jerry_value_is_error (typedarray));
      TEST_ASSERT (jerry_get_error_type (typedarray) == JERRY_ERROR_TYPE);
      jerry_release_value (typedarray);
    }

    jerry_release_value (arraybuffer);
  }

  /* Creating an TypedArray for a detached array buffer without length/offset is valid */
  {
    uint8_t buf[1];
    const uint32_t length = 1;
    jerry_value_t arraybuffer = jerry_create_arraybuffer_external (length, buf, NULL);
    TEST_ASSERT (!jerry_value_is_error (arraybuffer));
    TEST_ASSERT (jerry_value_is_arraybuffer (arraybuffer));
    TEST_ASSERT (jerry_get_arraybuffer_byte_length (arraybuffer) == length);

    jerry_value_t is_detachable = jerry_is_arraybuffer_detachable (arraybuffer);
    TEST_ASSERT (!jerry_value_is_error (is_detachable));
    TEST_ASSERT (jerry_get_boolean_value (is_detachable));
    jerry_release_value (is_detachable);

    jerry_value_t res = jerry_detach_arraybuffer (arraybuffer);
    TEST_ASSERT (!jerry_value_is_error (res));
    jerry_release_value (res);

    for (size_t idx = 0; idx < (sizeof (types) / sizeof (types[0])); idx++)
    {
      jerry_value_t typedarray = jerry_create_typedarray_for_arraybuffer (types[idx], arraybuffer);
      TEST_ASSERT (jerry_value_is_error (typedarray));
      TEST_ASSERT (jerry_get_error_type (typedarray) == JERRY_ERROR_TYPE);
      jerry_release_value (typedarray);
    }

    jerry_release_value (arraybuffer);
  }
}