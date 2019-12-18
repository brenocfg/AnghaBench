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
typedef  int /*<<< orphan*/  ecma_string_t ;
typedef  int /*<<< orphan*/  ecma_property_t ;
typedef  int /*<<< orphan*/  ecma_object_t ;
typedef  scalar_t__ ecma_lexical_environment_type_t ;

/* Variables and functions */
 scalar_t__ ECMA_LEXICAL_ENVIRONMENT_DECLARATIVE ; 
 scalar_t__ ECMA_LEXICAL_ENVIRONMENT_THIS_OBJECT_BOUND ; 
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 int /*<<< orphan*/ * ecma_find_named_property (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ecma_get_lex_env_binding_object (int /*<<< orphan*/ *) ; 
 scalar_t__ ecma_get_lex_env_type (int /*<<< orphan*/ *) ; 
 scalar_t__ ecma_is_lexical_environment (int /*<<< orphan*/ *) ; 
 int ecma_op_object_has_property (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool
ecma_op_has_binding (ecma_object_t *lex_env_p, /**< lexical environment */
                     ecma_string_t *name_p) /**< argument N */
{
  JERRY_ASSERT (lex_env_p != NULL
                && ecma_is_lexical_environment (lex_env_p));

  ecma_lexical_environment_type_t lex_env_type = ecma_get_lex_env_type (lex_env_p);

  if (lex_env_type == ECMA_LEXICAL_ENVIRONMENT_DECLARATIVE)
  {
    ecma_property_t *property_p = ecma_find_named_property (lex_env_p, name_p);

    return (property_p != NULL);
  }
  else
  {
    JERRY_ASSERT (lex_env_type == ECMA_LEXICAL_ENVIRONMENT_THIS_OBJECT_BOUND);

    ecma_object_t *binding_obj_p = ecma_get_lex_env_binding_object (lex_env_p);

    return ecma_op_object_has_property (binding_obj_p, name_p);
  }
}