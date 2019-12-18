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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ecma_value_t ;
typedef  int /*<<< orphan*/  ecma_builtin_helper_sort_compare_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECMA_FINALIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECMA_TRY_CATCH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECMA_VALUE_EMPTY ; 
 int /*<<< orphan*/  ecma_builtin_helper_array_to_heap (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 scalar_t__ ecma_is_value_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value ; 

ecma_value_t
ecma_builtin_helper_array_heap_sort_helper (ecma_value_t *array_p, /**< array to sort */
                                            uint32_t right, /**< right index */
                                            ecma_value_t compare_func, /**< compare function */
                                            const ecma_builtin_helper_sort_compare_fn_t sort_cb) /**< sorting cb */
{
  ecma_value_t ret_value = ECMA_VALUE_EMPTY;

  /* First, construct the ordered binary tree from the array. */
  for (uint32_t i = (right / 2) + 1; i > 0 && ecma_is_value_empty (ret_value); i--)
  {
    ECMA_TRY_CATCH (value,
                    ecma_builtin_helper_array_to_heap (array_p, i - 1, right, compare_func, sort_cb),
                    ret_value);
    ECMA_FINALIZE (value);
  }

  /* Sorting elements. */
  for (uint32_t i = right; i > 0 && ecma_is_value_empty (ret_value); i--)
  {
    /*
     * The top element will always contain the largest value.
     * Move top to the end, and remove it from the tree.
     */
    ecma_value_t swap = array_p[0];
    array_p[0] = array_p[i];
    array_p[i] = swap;

    /* Rebuild binary tree from the remaining elements. */
    ECMA_TRY_CATCH (value,
                    ecma_builtin_helper_array_to_heap (array_p, 0, i - 1, compare_func, sort_cb),
                    ret_value);
    ECMA_FINALIZE (value);
  }

  return ret_value;
}