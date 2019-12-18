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
typedef  int /*<<< orphan*/  ecma_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECMA_BUILTIN_ID_GLOBAL ; 
 int /*<<< orphan*/  ECMA_LEXICAL_ENVIRONMENT_THIS_OBJECT_BOUND ; 
 int /*<<< orphan*/  ECMA_SET_NON_NULL_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JERRY_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ecma_builtin_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ecma_create_object_lex_env (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_global_lex_env_cp ; 

void
ecma_init_global_lex_env (void)
{
  ecma_object_t *glob_obj_p = ecma_builtin_get (ECMA_BUILTIN_ID_GLOBAL);

  ecma_object_t *global_lex_env_p = ecma_create_object_lex_env (NULL,
                                                                glob_obj_p,
                                                                ECMA_LEXICAL_ENVIRONMENT_THIS_OBJECT_BOUND);
  ECMA_SET_NON_NULL_POINTER (JERRY_CONTEXT (ecma_global_lex_env_cp), global_lex_env_p);
}