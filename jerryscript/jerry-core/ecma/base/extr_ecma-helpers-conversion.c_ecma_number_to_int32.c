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
typedef  scalar_t__ const uint32_t ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  ecma_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 scalar_t__ ecma_number_to_uint32 (int /*<<< orphan*/ ) ; 

int32_t
ecma_number_to_int32 (ecma_number_t num) /**< ecma-number */
{
  uint32_t uint32_num = ecma_number_to_uint32 (num);

  /* 2 ^ 32 */
  const int64_t int64_2_pow_32 = (1ll << 32);

  /* 2 ^ 31 */
  const uint32_t uint32_2_pow_31 = (1ull << 31);

  int32_t ret;

  if (uint32_num >= uint32_2_pow_31)
  {
    ret = (int32_t) (uint32_num - int64_2_pow_32);
  }
  else
  {
    ret = (int32_t) uint32_num;
  }

#ifndef JERRY_NDEBUG
  int64_t int64_num = uint32_num;

  JERRY_ASSERT (int64_num >= 0);

  if (int64_num >= uint32_2_pow_31)
  {
    JERRY_ASSERT (ret == int64_num - int64_2_pow_32);
  }
  else
  {
    JERRY_ASSERT (ret == int64_num);
  }
#endif /* !JERRY_NDEBUG */

  return ret;
}