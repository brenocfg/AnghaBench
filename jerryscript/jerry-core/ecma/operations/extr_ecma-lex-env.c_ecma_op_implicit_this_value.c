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
typedef  int /*<<< orphan*/  ecma_object_t ;

/* Variables and functions */
 scalar_t__ ECMA_LEXICAL_ENVIRONMENT_DECLARATIVE ; 
 scalar_t__ ECMA_LEXICAL_ENVIRONMENT_THIS_OBJECT_BOUND ; 
 int /*<<< orphan*/  ECMA_VALUE_UNDEFINED ; 
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 int /*<<< orphan*/ * ecma_get_lex_env_binding_object (int /*<<< orphan*/ *) ; 
 scalar_t__ ecma_get_lex_env_type (int /*<<< orphan*/ *) ; 
 scalar_t__ ecma_is_lexical_environment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_make_object_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_ref_object (int /*<<< orphan*/ *) ; 

ecma_value_t
ecma_op_implicit_this_value (ecma_object_t *lex_env_p) /**< lexical environment */
{
  JERRY_ASSERT (lex_env_p != NULL
                && ecma_is_lexical_environment (lex_env_p));

  if (ecma_get_lex_env_type (lex_env_p) == ECMA_LEXICAL_ENVIRONMENT_DECLARATIVE)
  {
    return ECMA_VALUE_UNDEFINED;
  }
  else
  {
    JERRY_ASSERT (ecma_get_lex_env_type (lex_env_p) == ECMA_LEXICAL_ENVIRONMENT_THIS_OBJECT_BOUND);

    ecma_object_t *binding_obj_p = ecma_get_lex_env_binding_object (lex_env_p);
    ecma_ref_object (binding_obj_p);

    return ecma_make_object_value (binding_obj_p);
  }
}