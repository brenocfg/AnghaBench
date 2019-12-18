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
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 unsigned long LONG_MAX ; 
 int /*<<< orphan*/  TRUE ; 
 int ULONG_MAX ; 

__attribute__((used)) static svn_boolean_t
locale_independent_strtol(long *result_p,
                          const char* buffer,
                          const char** end)
{
  /* We allow positive values only.  We use unsigned arithmetics to get
   * well-defined overflow behavior.  It also happens to allow for a wider
   * range of compiler-side optimizations. */
  unsigned long result = 0;
  while (1)
    {
      unsigned long c = (unsigned char)*buffer - (unsigned char)'0';
      unsigned long next;

      /* This implies the NUL check. */
      if (c > 9)
        break;

      /* Overflow check.  Passing this, NEXT can be no more than ULONG_MAX+9
       * before being truncated to ULONG but it still covers 0 .. ULONG_MAX.
       */
      if (result > ULONG_MAX / 10)
        return FALSE;

      next = result * 10 + c;

      /* Overflow check.  In case of an overflow, NEXT is 0..9 and RESULT
       * is much larger than 10.  We will then return FALSE.
       *
       * In the non-overflow case, NEXT is >= 10 * RESULT but never smaller.
       * We will continue the loop in that case. */
      if (next < result)
        return FALSE;

      result = next;
      ++buffer;
    }

  *end = buffer;
  if (result > LONG_MAX)
    return FALSE;

  *result_p = (long)result;

  return TRUE;
}