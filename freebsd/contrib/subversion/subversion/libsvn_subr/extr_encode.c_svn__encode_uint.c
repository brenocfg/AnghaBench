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

unsigned char *
svn__encode_uint(unsigned char *p, apr_uint64_t val)
{
  int n;
  apr_uint64_t v;

  /* Figure out how many bytes we'll need.  */
  v = val >> 7;
  n = 1;
  while (v > 0)
    {
      v = v >> 7;
      n++;
    }

  /* Encode the remaining bytes; n is always the number of bytes
     coming after the one we're encoding.  */
  while (--n >= 1)
    *p++ = (unsigned char)(((val >> (n * 7)) | 0x80) & 0xff);

  *p++ = (unsigned char)(val & 0x7f);

  return p;
}