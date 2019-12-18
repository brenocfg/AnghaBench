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
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ecma_value_t ;
struct TYPE_5__ {int flags; int /*<<< orphan*/ * set_p; int /*<<< orphan*/ * get_p; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ ecma_property_descriptor_t ;
typedef  int /*<<< orphan*/  ecma_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECMA_ERR_MSG (char*) ; 
 int /*<<< orphan*/  ECMA_FINALIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECMA_IS_VALUE_ERROR (int /*<<< orphan*/ ) ; 
 int ECMA_PROP_IS_CONFIGURABLE ; 
 int ECMA_PROP_IS_CONFIGURABLE_DEFINED ; 
 int ECMA_PROP_IS_ENUMERABLE ; 
 int ECMA_PROP_IS_ENUMERABLE_DEFINED ; 
 int ECMA_PROP_IS_GET_DEFINED ; 
 int ECMA_PROP_IS_SET_DEFINED ; 
 int ECMA_PROP_IS_VALUE_DEFINED ; 
 int ECMA_PROP_IS_WRITABLE ; 
 int ECMA_PROP_IS_WRITABLE_DEFINED ; 
 int ECMA_PROP_NO_OPTS ; 
 int /*<<< orphan*/  ECMA_TRY_CATCH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECMA_VALUE_EMPTY ; 
 int /*<<< orphan*/  JERRY_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIT_MAGIC_STRING_CONFIGURABLE ; 
 int /*<<< orphan*/  LIT_MAGIC_STRING_ENUMERABLE ; 
 int /*<<< orphan*/  LIT_MAGIC_STRING_GET ; 
 int /*<<< orphan*/  LIT_MAGIC_STRING_SET ; 
 int /*<<< orphan*/  LIT_MAGIC_STRING_VALUE ; 
 int /*<<< orphan*/  LIT_MAGIC_STRING_WRITABLE ; 
 int /*<<< orphan*/  configurable_prop_value ; 
 int /*<<< orphan*/  ecma_copy_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_free_property_descriptor (TYPE_1__*) ; 
 int /*<<< orphan*/  ecma_get_magic_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ecma_get_object_from_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_is_value_empty (int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_is_value_found (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_is_value_object (int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_is_value_undefined (int /*<<< orphan*/ ) ; 
 TYPE_1__ ecma_make_empty_property_descriptor () ; 
 int /*<<< orphan*/  ecma_op_is_callable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_op_object_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_op_to_boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_raise_type_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_ref_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enumerable_prop_value ; 
 int /*<<< orphan*/  get_prop_value ; 
 int /*<<< orphan*/  set_prop_value ; 
 int /*<<< orphan*/  value_prop_value ; 
 int /*<<< orphan*/  writable_prop_value ; 

ecma_value_t
ecma_op_to_property_descriptor (ecma_value_t obj_value, /**< object value */
                                ecma_property_descriptor_t *out_prop_desc_p) /**< [out] filled property descriptor
                                                                                  if return value is normal
                                                                                  empty completion value */
{
  ecma_value_t ret_value = ECMA_VALUE_EMPTY;

  /* 1. */
  if (!ecma_is_value_object (obj_value))
  {
    ret_value = ecma_raise_type_error (ECMA_ERR_MSG ("Expected an object."));
  }
  else
  {
    ecma_object_t *obj_p = ecma_get_object_from_value (obj_value);

    /* 2. */
    ecma_property_descriptor_t prop_desc = ecma_make_empty_property_descriptor ();

    /* 3. */
    ECMA_TRY_CATCH (enumerable_prop_value,
                    ecma_op_object_find (obj_p, ecma_get_magic_string (LIT_MAGIC_STRING_ENUMERABLE)),
                    ret_value);

    if (ecma_is_value_found (enumerable_prop_value))
    {
      uint32_t is_enumerable = (ecma_op_to_boolean (enumerable_prop_value) ? ECMA_PROP_IS_ENUMERABLE
                                                                           : ECMA_PROP_NO_OPTS);

      prop_desc.flags |= (uint16_t) (ECMA_PROP_IS_ENUMERABLE_DEFINED | is_enumerable);
    }

    ECMA_FINALIZE (enumerable_prop_value);

    if (!ECMA_IS_VALUE_ERROR (ret_value))
    {
      JERRY_ASSERT (ecma_is_value_empty (ret_value));

      /* 4. */
      ECMA_TRY_CATCH (configurable_prop_value,
                      ecma_op_object_find (obj_p, ecma_get_magic_string (LIT_MAGIC_STRING_CONFIGURABLE)),
                      ret_value);

      if (ecma_is_value_found (configurable_prop_value))
      {
        uint32_t is_configurable = (ecma_op_to_boolean (configurable_prop_value) ? ECMA_PROP_IS_CONFIGURABLE
                                                                                 : ECMA_PROP_NO_OPTS);

        prop_desc.flags |= (uint16_t) (ECMA_PROP_IS_CONFIGURABLE_DEFINED | is_configurable);
      }

      ECMA_FINALIZE (configurable_prop_value);
    }

    if (!ECMA_IS_VALUE_ERROR (ret_value))
    {
      JERRY_ASSERT (ecma_is_value_empty (ret_value));

      /* 5. */
      ECMA_TRY_CATCH (value_prop_value,
                      ecma_op_object_find (obj_p, ecma_get_magic_string (LIT_MAGIC_STRING_VALUE)),
                      ret_value);

      if (ecma_is_value_found (value_prop_value))
      {
        prop_desc.flags |= ECMA_PROP_IS_VALUE_DEFINED;
        prop_desc.value = ecma_copy_value (value_prop_value);
      }

      ECMA_FINALIZE (value_prop_value);
    }

    if (!ECMA_IS_VALUE_ERROR (ret_value))
    {
      JERRY_ASSERT (ecma_is_value_empty (ret_value));

      /* 6. */
      ECMA_TRY_CATCH (writable_prop_value,
                      ecma_op_object_find (obj_p, ecma_get_magic_string (LIT_MAGIC_STRING_WRITABLE)),
                      ret_value);

      if (ecma_is_value_found (writable_prop_value))
      {
        uint32_t is_writable = (ecma_op_to_boolean (writable_prop_value) ? ECMA_PROP_IS_WRITABLE
                                                                         : ECMA_PROP_NO_OPTS);

        prop_desc.flags |= (uint16_t) (ECMA_PROP_IS_WRITABLE_DEFINED | is_writable);
      }

      ECMA_FINALIZE (writable_prop_value);
    }

    if (!ECMA_IS_VALUE_ERROR (ret_value))
    {
      JERRY_ASSERT (ecma_is_value_empty (ret_value));

      /* 7. */
      ECMA_TRY_CATCH (get_prop_value,
                      ecma_op_object_find (obj_p, ecma_get_magic_string (LIT_MAGIC_STRING_GET)),
                      ret_value);

      if (ecma_is_value_found (get_prop_value))
      {
        if (!ecma_op_is_callable (get_prop_value)
            && !ecma_is_value_undefined (get_prop_value))
        {
          ret_value = ecma_raise_type_error (ECMA_ERR_MSG ("Expected a function."));
        }
        else
        {
          prop_desc.flags |= ECMA_PROP_IS_GET_DEFINED;

          if (ecma_is_value_undefined (get_prop_value))
          {
            prop_desc.get_p = NULL;
          }
          else
          {
            JERRY_ASSERT (ecma_is_value_object (get_prop_value));

            ecma_object_t *get_p = ecma_get_object_from_value (get_prop_value);
            ecma_ref_object (get_p);

            prop_desc.get_p = get_p;
          }
        }
      }

      ECMA_FINALIZE (get_prop_value);
    }

    if (!ECMA_IS_VALUE_ERROR (ret_value))
    {
      JERRY_ASSERT (ecma_is_value_empty (ret_value));

      /* 8. */
      ECMA_TRY_CATCH (set_prop_value,
                      ecma_op_object_find (obj_p, ecma_get_magic_string (LIT_MAGIC_STRING_SET)),
                      ret_value);

      if (ecma_is_value_found (set_prop_value))
      {
        if (!ecma_op_is_callable (set_prop_value)
            && !ecma_is_value_undefined (set_prop_value))
        {
          ret_value = ecma_raise_type_error (ECMA_ERR_MSG ("Expected a function."));
        }
        else
        {
          prop_desc.flags |= ECMA_PROP_IS_SET_DEFINED;

          if (ecma_is_value_undefined (set_prop_value))
          {
            prop_desc.set_p = NULL;
          }
          else
          {
            JERRY_ASSERT (ecma_is_value_object (set_prop_value));

            ecma_object_t *set_p = ecma_get_object_from_value (set_prop_value);
            ecma_ref_object (set_p);

            prop_desc.set_p = set_p;
          }
        }
      }

      ECMA_FINALIZE (set_prop_value);
    }

    if (!ECMA_IS_VALUE_ERROR (ret_value))
    {
      JERRY_ASSERT (ecma_is_value_empty (ret_value));

      /* 9. */
      if ((prop_desc.flags & (ECMA_PROP_IS_VALUE_DEFINED | ECMA_PROP_IS_WRITABLE_DEFINED))
           && (prop_desc.flags & (ECMA_PROP_IS_GET_DEFINED | ECMA_PROP_IS_SET_DEFINED)))
      {
        ret_value = ecma_raise_type_error (ECMA_ERR_MSG ("Accessors cannot be writable."));
      }
    }

    if (!ECMA_IS_VALUE_ERROR (ret_value))
    {
      JERRY_ASSERT (ecma_is_value_empty (ret_value));
    }
    else
    {
      ecma_free_property_descriptor (&prop_desc);
    }

    *out_prop_desc_p = prop_desc;
  }

  return ret_value;
}