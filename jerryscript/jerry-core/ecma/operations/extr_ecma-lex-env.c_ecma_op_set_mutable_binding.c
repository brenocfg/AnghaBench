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
 int /*<<< orphan*/  ECMA_ERR_MSG (char*) ; 
 scalar_t__ ECMA_IS_VALUE_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ECMA_LEXICAL_ENVIRONMENT_DECLARATIVE ; 
 scalar_t__ ECMA_LEXICAL_ENVIRONMENT_THIS_OBJECT_BOUND ; 
 scalar_t__ ECMA_PROPERTY_GET_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ ECMA_PROPERTY_TYPE_NAMEDDATA ; 
 int /*<<< orphan*/  ECMA_PROPERTY_VALUE_PTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ECMA_VALUE_EMPTY ; 
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 int /*<<< orphan*/ * ecma_find_named_property (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ecma_get_lex_env_binding_object (int /*<<< orphan*/ *) ; 
 scalar_t__ ecma_get_lex_env_type (int /*<<< orphan*/ *) ; 
 scalar_t__ ecma_is_lexical_environment (int /*<<< orphan*/ *) ; 
 scalar_t__ ecma_is_property_writable (int /*<<< orphan*/ ) ; 
 int ecma_is_value_boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_named_data_property_assign_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_op_object_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecma_raise_type_error (int /*<<< orphan*/ ) ; 

ecma_value_t
ecma_op_set_mutable_binding (ecma_object_t *lex_env_p, /**< lexical environment */
                             ecma_string_t *name_p, /**< argument N */
                             ecma_value_t value, /**< argument V */
                             bool is_strict) /**< argument S */
{
  JERRY_ASSERT (lex_env_p != NULL
                && ecma_is_lexical_environment (lex_env_p));
  JERRY_ASSERT (name_p != NULL);

  if (ecma_get_lex_env_type (lex_env_p) == ECMA_LEXICAL_ENVIRONMENT_DECLARATIVE)
  {
    ecma_property_t *property_p = ecma_find_named_property (lex_env_p, name_p);

    JERRY_ASSERT (property_p != NULL
                  && ECMA_PROPERTY_GET_TYPE (*property_p) == ECMA_PROPERTY_TYPE_NAMEDDATA);

    if (ecma_is_property_writable (*property_p))
    {
      ecma_named_data_property_assign_value (lex_env_p, ECMA_PROPERTY_VALUE_PTR (property_p), value);
    }
    else if (is_strict)
    {
      return ecma_raise_type_error (ECMA_ERR_MSG ("Binding cannot be set."));
    }
  }
  else
  {
    JERRY_ASSERT (ecma_get_lex_env_type (lex_env_p) == ECMA_LEXICAL_ENVIRONMENT_THIS_OBJECT_BOUND);

    ecma_object_t *binding_obj_p = ecma_get_lex_env_binding_object (lex_env_p);

    ecma_value_t completion = ecma_op_object_put (binding_obj_p,
                                                  name_p,
                                                  value,
                                                  is_strict);

    if (ECMA_IS_VALUE_ERROR (completion))
    {
      return completion;
    }

    JERRY_ASSERT (ecma_is_value_boolean (completion));
  }

  return ECMA_VALUE_EMPTY;
}