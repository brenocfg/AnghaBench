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
typedef  int /*<<< orphan*/  digits ;
typedef  int apr_uint64_t ;

/* Variables and functions */
 int SVN_INT64_BUFFER_SIZE ; 

apr_uint64_t
svn__base36toui64(const char **next, const char *source)
{
  apr_uint64_t result = 0;
  apr_uint64_t factor = 1;
  int i  = 0;
  char digits[SVN_INT64_BUFFER_SIZE];

  /* convert digits to numerical values and count the number of places.
   * Also, prevent buffer overflow. */
  while (i < sizeof(digits))
    {
      char c = *source;
      if (c < 'a')
        {
          /* includes detection of NUL terminator */
          if (c < '0' || c > '9')
            break;

          c -= '0';
        }
      else
        {
          if (c < 'a' || c > 'z')
            break;

          c -= 'a' - 10;
        }

      digits[i++] = c;
      source++;
    }

  /* fold digits into the result */
  while (i > 0)
    {
      result += factor * (apr_uint64_t)digits[--i];
      factor *= 36;
    }

  if (next)
    *next = source;

  return result;
}