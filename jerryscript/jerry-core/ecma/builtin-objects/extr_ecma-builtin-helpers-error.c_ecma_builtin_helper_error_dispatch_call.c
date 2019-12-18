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
typedef  int /*<<< orphan*/  ecma_standard_error_t ;
typedef  int /*<<< orphan*/  ecma_object_t ;
typedef  scalar_t__ ecma_length_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECMA_VALUE_ERROR ; 
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 scalar_t__ JERRY_UNLIKELY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_deref_ecma_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_is_value_undefined (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ecma_make_object_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ecma_new_standard_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ecma_new_standard_error_with_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ecma_op_to_string (int /*<<< orphan*/  const) ; 

ecma_value_t
ecma_builtin_helper_error_dispatch_call (ecma_standard_error_t error_type, /**< native error type */
                                         const ecma_value_t *arguments_list_p, /**< arguments list */
                                         ecma_length_t arguments_list_len) /**< number of arguments */
{
  JERRY_ASSERT (arguments_list_len == 0 || arguments_list_p != NULL);

  if (arguments_list_len != 0
      && !ecma_is_value_undefined (arguments_list_p[0]))
  {
    ecma_string_t *message_string_p = ecma_op_to_string (arguments_list_p[0]);

    if (JERRY_UNLIKELY (message_string_p == NULL))
    {
      return ECMA_VALUE_ERROR;
    }

    ecma_object_t *new_error_object_p = ecma_new_standard_error_with_message (error_type,
                                                                              message_string_p);

    ecma_deref_ecma_string (message_string_p);
    return ecma_make_object_value (new_error_object_p);
  }
  else
  {
    ecma_object_t *new_error_object_p = ecma_new_standard_error (error_type);

    return ecma_make_object_value (new_error_object_p);
  }
}