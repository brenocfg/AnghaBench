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
typedef  int /*<<< orphan*/  uInt ;
typedef  int apr_uint32_t ;
typedef  int apr_off_t ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int ADLER_MOD_BASE ; 
 int /*<<< orphan*/  adler32 (int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

apr_uint32_t
svn__adler32(apr_uint32_t checksum, const char *data, apr_off_t len)
{
  /* The actual limit can be set somewhat higher but should
   * not be lower because the SIMD code would not be used
   * in that case.
   *
   * However, it must be lower than 5552 to make sure our local
   * implementation does not suffer from overflows.
   */
  if (len >= 80)
    {
      /* Larger buffers can be efficiently handled by Marc Adler's
       * optimized code. Also, new zlib versions will come with
       * SIMD code for x86 and x64.
       */
      return (apr_uint32_t)adler32(checksum,
                                   (const Bytef *)data,
                                   (uInt)len);
    }
  else
    {
      const unsigned char *input = (const unsigned char *)data;
      apr_uint32_t s1 = checksum & 0xFFFF;
      apr_uint32_t s2 = checksum >> 16;
      apr_uint32_t b;

      /* Some loop unrolling
       * (approx. one clock tick per byte + 2 ticks loop overhead)
       */
      for (; len >= 8; len -= 8, input += 8)
        {
          s1 += input[0]; s2 += s1;
          s1 += input[1]; s2 += s1;
          s1 += input[2]; s2 += s1;
          s1 += input[3]; s2 += s1;
          s1 += input[4]; s2 += s1;
          s1 += input[5]; s2 += s1;
          s1 += input[6]; s2 += s1;
          s1 += input[7]; s2 += s1;
        }

      /* Adler-32 calculation as a simple two ticks per iteration loop.
       */
      while (len--)
        {
          b = *input++;
          s1 += b;
          s2 += s1;
        }

      return ((s2 % ADLER_MOD_BASE) << 16) | (s1 % ADLER_MOD_BASE);
    }
}