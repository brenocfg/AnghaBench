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

/* Variables and functions */
 scalar_t__ STACK_MAGIC ; 
 scalar_t__ __HeapLimit ; 

__attribute__((used)) static __attribute__((noinline)) uint32_t measure_stack(void)
{
  uint32_t *stack_start = &__HeapLimit;
  uint32_t ss, *stack_stop = &ss;
  size_t words = stack_stop - stack_start;
  for (size_t i = 0; i < words; i++)
    if (stack_start[i] != STACK_MAGIC)
      return words - i + 4; /* we used 4 words for ourselves, roughly */

  return 0;
}