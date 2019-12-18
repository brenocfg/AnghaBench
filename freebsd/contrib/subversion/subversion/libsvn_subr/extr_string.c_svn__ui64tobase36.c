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
typedef  scalar_t__ value ;
typedef  int apr_uint64_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int SVN_INT64_BUFFER_SIZE ; 

apr_size_t
svn__ui64tobase36(char *dest, apr_uint64_t value)
{
  char *dest_start = dest;
  if (value < 10)
    {
      /* pretty frequent and trivial case. Make it fast. */
      *(dest++) = (char)(value) + '0';
    }
  else
    {
      char buffer[SVN_INT64_BUFFER_SIZE];
      char *p = buffer;

      /* write result as little-endian to buffer */
      while (value > 0)
        {
          char c = (char)(value % 36);
          value /= 36;

          *p = (c <= 9) ? (c + '0') : (c - 10 + 'a');
          ++p;
        }

      /* copy as big-endian to DEST */
      while (p > buffer)
        *(dest++) = *(--p);
    }

  *dest = '\0';
  return dest - dest_start;
}