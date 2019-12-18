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
typedef  int apr_uint32_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_TWO_BYTES (char*,int /*<<< orphan*/ ) ; 
 int SVN_INT64_BUFFER_SIZE ; 
 int /*<<< orphan*/ * decimal_table ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

apr_size_t
svn__ui64toa(char * dest, apr_uint64_t number)
{
  char buffer[SVN_INT64_BUFFER_SIZE];
  apr_uint32_t reduced;   /* used for 32 bit DIV */
  char* target;

  /* Small numbers are by far the most common case.
   * Therefore, we use special code.
   */
  if (number < 100)
    {
      if (number < 10)
        {
          dest[0] = (char)('0' + number);
          dest[1] = 0;
          return 1;
        }
      else
        {
          COPY_TWO_BYTES(dest, decimal_table[(apr_size_t)number]);
          dest[2] = 0;
          return 2;
        }
    }

  /* Standard code. Write string in pairs of chars back-to-front */
  buffer[SVN_INT64_BUFFER_SIZE - 1] = 0;
  target = &buffer[SVN_INT64_BUFFER_SIZE - 3];

  /* Loop may be executed 0 .. 2 times. */
  while (number >= 100000000)
    {
      /* Number is larger than 100^4, i.e. we can write 4x2 chars.
       * Also, use 32 bit DIVs as these are about twice as fast.
       */
      reduced = (apr_uint32_t)(number % 100000000);
      number /= 100000000;

      COPY_TWO_BYTES(target - 0, decimal_table[reduced % 100]);
      reduced /= 100;
      COPY_TWO_BYTES(target - 2, decimal_table[reduced % 100]);
      reduced /= 100;
      COPY_TWO_BYTES(target - 4, decimal_table[reduced % 100]);
      reduced /= 100;
      COPY_TWO_BYTES(target - 6, decimal_table[reduced % 100]);
      target -= 8;
    }

  /* Now, the number fits into 32 bits, but may still be larger than 99 */
  reduced = (apr_uint32_t)(number);
  while (reduced >= 100)
    {
      COPY_TWO_BYTES(target, decimal_table[reduced % 100]);
      reduced /= 100;
      target -= 2;
    }

  /* The number is now smaller than 100 but larger than 1 */
  COPY_TWO_BYTES(target, decimal_table[reduced]);

  /* Correction for uneven count of places. */
  if (reduced < 10)
    ++target;

  /* Copy to target */
  memcpy(dest, target, &buffer[SVN_INT64_BUFFER_SIZE] - target);
  return &buffer[SVN_INT64_BUFFER_SIZE] - target - 1;
}