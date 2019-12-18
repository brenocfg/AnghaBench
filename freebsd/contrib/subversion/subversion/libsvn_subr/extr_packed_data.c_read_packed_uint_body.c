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
typedef  int apr_uint64_t ;

/* Variables and functions */

__attribute__((used)) static unsigned char *
read_packed_uint_body(unsigned char *p, apr_uint64_t *result)
{
  if (*p < 0x80)
    {
      *result = *p;
    }
  else
    {
      apr_uint64_t shift = 0;
      apr_uint64_t value = 0;
      while (*p >= 0x80)
        {
          value += (apr_uint64_t)(*p & 0x7f) << shift;
          ++p;

          shift += 7;
          if (shift > 64)
            {
              /* a definite overflow.  Note, that numbers of 65 .. 70
                 bits will not be detected as an overflow as they don't
                 threaten to exceed the input buffer. */
              *result = 0;
              return p;
            }
        }

      *result = value + ((apr_uint64_t)*p << shift);
    }

  return ++p;
}