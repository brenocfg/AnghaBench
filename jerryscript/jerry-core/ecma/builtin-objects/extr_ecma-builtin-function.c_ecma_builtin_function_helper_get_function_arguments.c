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
typedef  int ecma_length_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECMA_VALUE_ERROR ; 
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 scalar_t__ JERRY_UNLIKELY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIT_MAGIC_STRING_COMMA_CHAR ; 
 int /*<<< orphan*/  LIT_MAGIC_STRING__EMPTY ; 
 int /*<<< orphan*/ * ecma_append_magic_string_to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ecma_concat_ecma_strings (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_deref_ecma_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_make_magic_string_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_make_string_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ecma_op_to_string (int /*<<< orphan*/  const) ; 

__attribute__((used)) static ecma_value_t
ecma_builtin_function_helper_get_function_arguments (const ecma_value_t *arguments_list_p, /**< arguments list */
                                                     ecma_length_t arguments_list_len) /**< number of arguments */
{
  JERRY_ASSERT (arguments_list_len == 0 || arguments_list_p != NULL);

  if (arguments_list_len <= 1)
  {
    return ecma_make_magic_string_value (LIT_MAGIC_STRING__EMPTY);
  }

  ecma_string_t *final_str_p = ecma_op_to_string (arguments_list_p[0]);

  if (JERRY_UNLIKELY (final_str_p == NULL))
  {
    return ECMA_VALUE_ERROR;
  }

  if (arguments_list_len == 2)
  {
    return ecma_make_string_value (final_str_p);
  }

  for (ecma_length_t idx = 1; idx < arguments_list_len - 1; idx++)
  {
    ecma_string_t *new_str_p = ecma_op_to_string (arguments_list_p[idx]);

    if (JERRY_UNLIKELY (new_str_p == NULL))
    {
      ecma_deref_ecma_string (final_str_p);
      return ECMA_VALUE_ERROR;
    }

    final_str_p = ecma_append_magic_string_to_string (final_str_p,
                                                      LIT_MAGIC_STRING_COMMA_CHAR);

    final_str_p = ecma_concat_ecma_strings (final_str_p, new_str_p);
    ecma_deref_ecma_string (new_str_p);
  }

  return ecma_make_string_value (final_str_p);
}