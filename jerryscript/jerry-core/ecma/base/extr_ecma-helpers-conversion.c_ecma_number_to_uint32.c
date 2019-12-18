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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ const uint32_t ;
typedef  scalar_t__ ecma_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 scalar_t__ ecma_number_calc_remainder (scalar_t__ const,scalar_t__ const) ; 
 scalar_t__ ecma_number_is_infinity (scalar_t__) ; 
 scalar_t__ ecma_number_is_nan (scalar_t__) ; 
 int ecma_number_is_negative (scalar_t__) ; 
 scalar_t__ ecma_number_is_zero (scalar_t__) ; 

uint32_t
ecma_number_to_uint32 (ecma_number_t num) /**< ecma-number */
{
  if (ecma_number_is_nan (num)
      || ecma_number_is_zero (num)
      || ecma_number_is_infinity (num))
  {
    return 0;
  }

  const bool sign = ecma_number_is_negative (num);
  const ecma_number_t abs_num = sign ? -num : num;

  /* 2 ^ 32 */
  const uint64_t uint64_2_pow_32 = (1ull << 32);

  const ecma_number_t num_2_pow_32 = (float) uint64_2_pow_32;

  ecma_number_t num_in_uint32_range;

  if (abs_num >= num_2_pow_32)
  {
    num_in_uint32_range = ecma_number_calc_remainder (abs_num,
                                                      num_2_pow_32);
  }
  else
  {
    num_in_uint32_range = abs_num;
  }

  /* Check that the floating point value can be represented with uint32_t. */
  JERRY_ASSERT (num_in_uint32_range < uint64_2_pow_32);
  uint32_t uint32_num = (uint32_t) num_in_uint32_range;

  const uint32_t ret = sign ? -uint32_num : uint32_num;

#ifndef JERRY_NDEBUG
  if (sign
      && uint32_num != 0)
  {
    JERRY_ASSERT (ret == uint64_2_pow_32 - uint32_num);
  }
  else
  {
    JERRY_ASSERT (ret == uint32_num);
  }
#endif /* !JERRY_NDEBUG */

  return ret;
}