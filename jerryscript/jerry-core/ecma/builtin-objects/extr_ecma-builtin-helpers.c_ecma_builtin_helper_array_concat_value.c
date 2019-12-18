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
typedef  int /*<<< orphan*/  ecma_value_t ;
typedef  int /*<<< orphan*/  ecma_object_t ;

/* Variables and functions */
 scalar_t__ ECMA_IS_VALUE_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ECMA_OBJECT_TYPE_ARRAY ; 
 int /*<<< orphan*/  ECMA_PROPERTY_CONFIGURABLE_ENUMERABLE_WRITABLE ; 
 int /*<<< orphan*/  ECMA_VALUE_EMPTY ; 
 int /*<<< orphan*/  JERRY_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_array_get_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_builtin_helper_def_prop_by_index (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_free_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ecma_get_object_from_value (int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_get_object_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_is_value_found (int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_is_value_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_is_value_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_op_object_find_by_uint32_index (int /*<<< orphan*/ *,scalar_t__) ; 

ecma_value_t
ecma_builtin_helper_array_concat_value (ecma_object_t *array_obj_p, /**< array */
                                        uint32_t *length_p, /**< [in,out] array's length */
                                        ecma_value_t value) /**< value to concat */
{
  /* 5.b */
  if (ecma_is_value_object (value))
  {
    ecma_object_t *obj_p = ecma_get_object_from_value (value);

    if (ecma_get_object_type (obj_p) == ECMA_OBJECT_TYPE_ARRAY)
    {
      /* 5.b.ii */
      uint32_t arg_len = ecma_array_get_length (obj_p);

      /* 5.b.iii */
      for (uint32_t array_index = 0; array_index < arg_len; array_index++)
      {
        /* 5.b.iii.2 */
        ecma_value_t get_value = ecma_op_object_find_by_uint32_index (obj_p, array_index);

        if (ECMA_IS_VALUE_ERROR (get_value))
        {
          return get_value;
        }

        if (!ecma_is_value_found (get_value))
        {
          continue;
        }

        /* 5.b.iii.3.b */
        /* This will always be a simple value since 'is_throw' is false, so no need to free. */
        ecma_value_t put_comp = ecma_builtin_helper_def_prop_by_index (array_obj_p,
                                                                       *length_p + array_index,
                                                                       get_value,
                                                                       ECMA_PROPERTY_CONFIGURABLE_ENUMERABLE_WRITABLE);

        JERRY_ASSERT (ecma_is_value_true (put_comp));
        ecma_free_value (get_value);
      }

      *length_p += arg_len;
      return ECMA_VALUE_EMPTY;
    }
  }

  /* 5.c.i */
  /* This will always be a simple value since 'is_throw' is false, so no need to free. */
  ecma_value_t put_comp = ecma_builtin_helper_def_prop_by_index (array_obj_p,
                                                                 (*length_p)++,
                                                                 value,
                                                                 ECMA_PROPERTY_CONFIGURABLE_ENUMERABLE_WRITABLE);
  JERRY_ASSERT (ecma_is_value_true (put_comp));

  return ECMA_VALUE_EMPTY;
}