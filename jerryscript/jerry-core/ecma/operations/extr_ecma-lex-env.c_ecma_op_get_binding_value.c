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
typedef  int /*<<< orphan*/  ecma_value_t ;
typedef  int /*<<< orphan*/  ecma_string_t ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ ecma_property_value_t ;
typedef  int /*<<< orphan*/  ecma_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECMA_ERR_MSG (char*) ; 
 scalar_t__ ECMA_LEXICAL_ENVIRONMENT_DECLARATIVE ; 
 scalar_t__ ECMA_LEXICAL_ENVIRONMENT_THIS_OBJECT_BOUND ; 
 int /*<<< orphan*/  ECMA_VALUE_UNDEFINED ; 
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 int /*<<< orphan*/  ecma_copy_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ecma_get_lex_env_binding_object (int /*<<< orphan*/ *) ; 
 scalar_t__ ecma_get_lex_env_type (int /*<<< orphan*/ *) ; 
 TYPE_1__* ecma_get_named_data_property (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ecma_is_lexical_environment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_is_value_found (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_op_object_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_raise_reference_error (int /*<<< orphan*/ ) ; 

ecma_value_t
ecma_op_get_binding_value (ecma_object_t *lex_env_p, /**< lexical environment */
                           ecma_string_t *name_p, /**< argument N */
                           bool is_strict) /**< argument S */
{
  JERRY_ASSERT (lex_env_p != NULL
                && ecma_is_lexical_environment (lex_env_p));
  JERRY_ASSERT (name_p != NULL);

  if (ecma_get_lex_env_type (lex_env_p) == ECMA_LEXICAL_ENVIRONMENT_DECLARATIVE)
  {
    ecma_property_value_t *prop_value_p = ecma_get_named_data_property (lex_env_p, name_p);

    return ecma_copy_value (prop_value_p->value);
  }
  else
  {
    JERRY_ASSERT (ecma_get_lex_env_type (lex_env_p) == ECMA_LEXICAL_ENVIRONMENT_THIS_OBJECT_BOUND);

    ecma_object_t *binding_obj_p = ecma_get_lex_env_binding_object (lex_env_p);

    ecma_value_t result = ecma_op_object_find (binding_obj_p, name_p);

    if (!ecma_is_value_found (result))
    {
      if (is_strict)
      {
        result = ecma_raise_reference_error (ECMA_ERR_MSG ("Binding does not exist or is uninitialised."));
      }
      else
      {
        result = ECMA_VALUE_UNDEFINED;
      }
    }

    return result;
  }
}