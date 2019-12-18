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
typedef  int /*<<< orphan*/  ecma_string_t ;
typedef  int /*<<< orphan*/  ecma_object_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ECMA_CREATE_DIRECT_UINT32_STRING (scalar_t__) ; 
 scalar_t__ ECMA_DIRECT_STRING_MAX_IMM ; 
 scalar_t__ JERRY_LIKELY (int) ; 
 int /*<<< orphan*/  ecma_builtin_helper_def_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ecma_deref_ecma_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ecma_new_non_direct_string_from_uint32 (scalar_t__) ; 

ecma_value_t
ecma_builtin_helper_def_prop_by_index (ecma_object_t *obj_p, /**< object */
                                       uint32_t index, /**< property index */
                                       ecma_value_t value, /**< value */
                                       uint32_t opts) /**< any combination of ecma_property_flag_t bits */
{
  if (JERRY_LIKELY (index <= ECMA_DIRECT_STRING_MAX_IMM))
  {
    return ecma_builtin_helper_def_prop (obj_p,
                                         ECMA_CREATE_DIRECT_UINT32_STRING (index),
                                         value,
                                         opts);
  }

  ecma_string_t *index_str_p = ecma_new_non_direct_string_from_uint32 (index);
  ecma_value_t ret_value = ecma_builtin_helper_def_prop (obj_p,
                                                         index_str_p,
                                                         value,
                                                         opts);
  ecma_deref_ecma_string (index_str_p);

  return ret_value;
}