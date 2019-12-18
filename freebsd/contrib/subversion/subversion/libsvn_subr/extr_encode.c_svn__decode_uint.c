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
 int SVN__MAX_ENCODED_UINT_LEN ; 
 scalar_t__ SVN__PREDICT_TRUE (int) ; 

const unsigned char *
svn__decode_uint(apr_uint64_t *val,
                 const unsigned char *p,
                 const unsigned char *end)
{
  apr_uint64_t temp = 0;

  if (end - p > SVN__MAX_ENCODED_UINT_LEN)
    end = p + SVN__MAX_ENCODED_UINT_LEN;

  /* Decode bytes until we're done. */
  while (SVN__PREDICT_TRUE(p < end))
    {
      unsigned int c = *p++;

      if (c < 0x80)
        {
          *val = (temp << 7) | c;
          return p;
        }
      else
        {
          temp = (temp << 7) | (c & 0x7f);
        }
    }

  return NULL;
}