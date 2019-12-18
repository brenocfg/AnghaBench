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
typedef  int /*<<< orphan*/  ecma_value_t ;
typedef  int /*<<< orphan*/  ecma_string_t ;
typedef  int /*<<< orphan*/  ecma_property_t ;
typedef  int /*<<< orphan*/  ecma_object_t ;

/* Variables and functions */
 scalar_t__ ECMA_LEXICAL_ENVIRONMENT_DECLARATIVE ; 
 scalar_t__ ECMA_LEXICAL_ENVIRONMENT_THIS_OBJECT_BOUND ; 
 scalar_t__ ECMA_PROPERTY_GET_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ ECMA_PROPERTY_TYPE_NAMEDDATA ; 
 int /*<<< orphan*/  ECMA_PROPERTY_VALUE_PTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ECMA_VALUE_FALSE ; 
 int /*<<< orphan*/  ECMA_VALUE_TRUE ; 
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 int /*<<< orphan*/  ecma_delete_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ecma_find_named_property (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ecma_get_lex_env_binding_object (int /*<<< orphan*/ *) ; 
 scalar_t__ ecma_get_lex_env_type (int /*<<< orphan*/ *) ; 
 scalar_t__ ecma_is_lexical_environment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_is_property_configurable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_op_object_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

ecma_value_t
ecma_op_delete_binding (ecma_object_t *lex_env_p, /**< lexical environment */
                        ecma_string_t *name_p) /**< argument N */
{
  JERRY_ASSERT (lex_env_p != NULL
                && ecma_is_lexical_environment (lex_env_p));
  JERRY_ASSERT (name_p != NULL);


  if (ecma_get_lex_env_type (lex_env_p) == ECMA_LEXICAL_ENVIRONMENT_DECLARATIVE)
  {
    ecma_property_t *prop_p = ecma_find_named_property (lex_env_p, name_p);
    ecma_value_t ret_val;

    if (prop_p == NULL)
    {
      ret_val = ECMA_VALUE_TRUE;
    }
    else
    {
      JERRY_ASSERT (ECMA_PROPERTY_GET_TYPE (*prop_p) == ECMA_PROPERTY_TYPE_NAMEDDATA);

      if (!ecma_is_property_configurable (*prop_p))
      {
        ret_val = ECMA_VALUE_FALSE;
      }
      else
      {
        ecma_delete_property (lex_env_p, ECMA_PROPERTY_VALUE_PTR (prop_p));

        ret_val = ECMA_VALUE_TRUE;
      }
    }

    return ret_val;
  }
  else
  {
    JERRY_ASSERT (ecma_get_lex_env_type (lex_env_p) == ECMA_LEXICAL_ENVIRONMENT_THIS_OBJECT_BOUND);

    ecma_object_t *binding_obj_p = ecma_get_lex_env_binding_object (lex_env_p);

    return ecma_op_object_delete (binding_obj_p, name_p, false);
  }
}