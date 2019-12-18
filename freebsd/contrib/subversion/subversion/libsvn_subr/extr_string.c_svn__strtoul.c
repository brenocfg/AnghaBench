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

/* Variables and functions */

unsigned long
svn__strtoul(const char* buffer, const char** end)
{
  unsigned long result = 0;

  /* this loop will execute in just 2 CPU cycles, confirmed by measurement:
     7 macro-ops (max 4 / cycle => 2 cycles)
       1 load (max 1 / cycle)
       1 jumps (compare + conditional jump == 1 macro op; max 1 / cycle)
       2 arithmetic ops (subtract, increment; max 3 / cycle)
       2 scale-and-add AGU ops (max 3 / cycle)
       1 compiler-generated move operation
     dependency chain: temp = result * 4 + result; result = temp * 2 + c
                       (2 ops with latency 1 => 2 cycles)
   */
  while (1)
    {
      unsigned long c = (unsigned char)*buffer - (unsigned char)'0';
      if (c > 9)
        break;

      result = result * 10 + c;
      ++buffer;
    }

  *end = buffer;
  return result;
}