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
typedef  scalar_t__ apr_size_t ;
typedef  int apr_int32_t ;

/* Variables and functions */

__attribute__((used)) static int
ucs4cmp(const apr_int32_t *bufa, apr_size_t lena,
        const apr_int32_t *bufb, apr_size_t lenb)
{
  const apr_size_t len = (lena < lenb ? lena : lenb);
  apr_size_t i;

  for (i = 0; i < len; ++i)
    {
      const int diff = bufa[i] - bufb[i];
      if (diff)
        return diff;
    }
  return (lena == lenb ? 0 : (lena < lenb ? -1 : 1));
}