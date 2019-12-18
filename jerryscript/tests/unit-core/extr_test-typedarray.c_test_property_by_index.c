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
typedef  int uint8_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  test_int_numbers ;
struct TYPE_3__ {int /*<<< orphan*/  typedarray_type; int /*<<< orphan*/ * constructor_name; } ;
typedef  TYPE_1__ test_entry_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  int jerry_typedarray_type_t ;

/* Variables and functions */
#define  JERRY_TYPEDARRAY_FLOAT32 132 
#define  JERRY_TYPEDARRAY_FLOAT64 131 
#define  JERRY_TYPEDARRAY_INT16 130 
#define  JERRY_TYPEDARRAY_INT32 129 
#define  JERRY_TYPEDARRAY_INT8 128 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 double fabs (int /*<<< orphan*/ ) ; 
 int isinf (int) ; 
 int /*<<< orphan*/  jerry_create_number (int) ; 
 int /*<<< orphan*/  jerry_create_number_infinity (int) ; 
 int /*<<< orphan*/  jerry_create_typedarray (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  jerry_delete_property_by_index (int /*<<< orphan*/ ,int) ; 
 int jerry_get_boolean_value (int /*<<< orphan*/ ) ; 
 int jerry_get_number_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_get_property_by_index (int /*<<< orphan*/ ,int) ; 
 int jerry_get_typedarray_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_set_property_by_index (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int jerry_value_is_boolean (int /*<<< orphan*/ ) ; 
 int jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int jerry_value_is_undefined (int /*<<< orphan*/ ) ; 
 double pow (int,int) ; 

__attribute__((used)) static void test_property_by_index (test_entry_t test_entries[])
{
  int test_int_numbers[5] = {-5, -70, 13, 0, 56};
  double test_double_numbers[5] = {-83.153, -35.15, 0, 13.1, 89.8975};
  uint8_t test_uint_numbers[5] = {83, 15, 36, 0, 43};

  for (uint32_t i = 0; test_entries[i].constructor_name != NULL; i++)
  {
    jerry_value_t test_number;
    uint32_t test_numbers_length = sizeof (test_int_numbers) / sizeof (int);
    jerry_value_t typedarray = jerry_create_typedarray (test_entries[i].typedarray_type, test_numbers_length);
    jerry_typedarray_type_t type = jerry_get_typedarray_type (typedarray);

    jerry_value_t set_result;
    jerry_value_t get_result;

    switch (type)
    {
      case JERRY_TYPEDARRAY_INT8:
      case JERRY_TYPEDARRAY_INT16:
      case JERRY_TYPEDARRAY_INT32:
      {
        for (uint8_t j = 0; j < test_numbers_length; j++)
        {
          test_number = jerry_create_number (test_int_numbers[j]);
          TEST_ASSERT (!jerry_delete_property_by_index (typedarray, j));
          set_result = jerry_set_property_by_index (typedarray, j, test_number);
          get_result = jerry_get_property_by_index (typedarray, j);

          TEST_ASSERT (jerry_value_is_boolean (set_result));
          TEST_ASSERT (jerry_get_boolean_value (set_result));
          TEST_ASSERT (!jerry_delete_property_by_index (typedarray, j));
          TEST_ASSERT (jerry_get_number_value (get_result) == test_int_numbers[j]);

          jerry_release_value (test_number);
          jerry_release_value (set_result);
          jerry_release_value (get_result);
        }
        break;
      }
      case JERRY_TYPEDARRAY_FLOAT32:
      case JERRY_TYPEDARRAY_FLOAT64:
      {
        for (uint8_t j = 0; j < test_numbers_length; j++)
        {
          test_number = jerry_create_number (test_double_numbers[j]);
          TEST_ASSERT (!jerry_delete_property_by_index (typedarray, j));
          set_result = jerry_set_property_by_index (typedarray, j, test_number);
          get_result = jerry_get_property_by_index (typedarray, j);

          TEST_ASSERT (jerry_value_is_boolean (set_result));
          TEST_ASSERT (jerry_get_boolean_value (set_result));
          TEST_ASSERT (!jerry_delete_property_by_index (typedarray, j));

          double epsilon = pow (10, -5);
          double get_abs = fabs (jerry_get_number_value (get_result) - test_double_numbers[j]);
          TEST_ASSERT (get_abs < epsilon);

          jerry_release_value (test_number);
          jerry_release_value (set_result);
          jerry_release_value (get_result);

          /* Testing positive and negative infinity */
          for (uint8_t k = 0; k < 2; k++)
          {
            jerry_value_t inf = jerry_create_number_infinity (k);
            jerry_value_t set_inf = jerry_set_property_by_index (typedarray, 0, inf);
            TEST_ASSERT (jerry_value_is_boolean (set_inf));
            TEST_ASSERT (jerry_get_boolean_value (set_inf));
            jerry_value_t get_inf = jerry_get_property_by_index (typedarray, 0);
            TEST_ASSERT (isinf (jerry_get_number_value (get_inf)));

            jerry_release_value (inf);
            jerry_release_value (set_inf);
            jerry_release_value (get_inf);
          }
        }
        break;
      }
      default:
      {
        for (uint8_t j = 0; j < test_numbers_length; j++)
        {
          test_number = jerry_create_number (test_uint_numbers[j]);
          TEST_ASSERT (!jerry_delete_property_by_index (typedarray, j));
          set_result = jerry_set_property_by_index (typedarray, j, test_number);
          get_result = jerry_get_property_by_index (typedarray, j);

          TEST_ASSERT (jerry_value_is_boolean (set_result));
          TEST_ASSERT (jerry_get_boolean_value (set_result));
          TEST_ASSERT (!jerry_delete_property_by_index (typedarray, j));
          TEST_ASSERT (jerry_get_number_value (get_result) == test_uint_numbers[j]);

          jerry_release_value (test_number);
          jerry_release_value (set_result);
          jerry_release_value (get_result);
        }
        break;
      }
    }

    jerry_value_t set_undefined = jerry_set_property_by_index (typedarray, 100, jerry_create_number (50));
    TEST_ASSERT (jerry_value_is_error (set_undefined));
    jerry_value_t get_undefined = jerry_get_property_by_index (typedarray, 100);
    TEST_ASSERT (jerry_value_is_undefined (get_undefined));

    jerry_release_value (set_undefined);
    jerry_release_value (get_undefined);
    jerry_release_value (typedarray);
  }
}