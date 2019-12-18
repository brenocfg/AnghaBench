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
typedef  int uint32_t ;
typedef  scalar_t__ lit_utf8_size_t ;
typedef  int lit_utf8_byte_t ;
typedef  int lit_code_point_t ;

/* Variables and functions */
 int LIT_UTF8_1_BYTE_MARKER ; 
 int LIT_UTF8_1_BYTE_MASK ; 
 int LIT_UTF8_2_BYTE_CODE_POINT_MIN ; 
 int LIT_UTF8_2_BYTE_MARKER ; 
 int LIT_UTF8_2_BYTE_MASK ; 
 int LIT_UTF8_3_BYTE_CODE_POINT_MIN ; 
 int LIT_UTF8_3_BYTE_MARKER ; 
 int LIT_UTF8_3_BYTE_MASK ; 
 int LIT_UTF8_BITS_IN_EXTRA_BYTES ; 
 int LIT_UTF8_EXTRA_BYTE_MARKER ; 
 int LIT_UTF8_EXTRA_BYTE_MASK ; 
 int LIT_UTF8_LAST_4_BITS_MASK ; 
 int LIT_UTF8_LAST_5_BITS_MASK ; 
 int LIT_UTF8_LAST_6_BITS_MASK ; 

bool
lit_is_valid_cesu8_string (const lit_utf8_byte_t *cesu8_buf_p, /**< cesu-8 string */
                           lit_utf8_size_t buf_size) /**< string size */
{
  lit_utf8_size_t idx = 0;

  while (idx < buf_size)
  {
    lit_utf8_byte_t c = cesu8_buf_p[idx++];
    if ((c & LIT_UTF8_1_BYTE_MASK) == LIT_UTF8_1_BYTE_MARKER)
    {
      continue;
    }

    lit_code_point_t code_point = 0;
    lit_code_point_t min_code_point = 0;
    lit_utf8_size_t extra_bytes_count;
    if ((c & LIT_UTF8_2_BYTE_MASK) == LIT_UTF8_2_BYTE_MARKER)
    {
      extra_bytes_count = 1;
      min_code_point = LIT_UTF8_2_BYTE_CODE_POINT_MIN;
      code_point = ((uint32_t) (c & LIT_UTF8_LAST_5_BITS_MASK));
    }
    else if ((c & LIT_UTF8_3_BYTE_MASK) == LIT_UTF8_3_BYTE_MARKER)
    {
      extra_bytes_count = 2;
      min_code_point = LIT_UTF8_3_BYTE_CODE_POINT_MIN;
      code_point = ((uint32_t) (c & LIT_UTF8_LAST_4_BITS_MASK));
    }
    else
    {
      return false;
    }

    if (idx + extra_bytes_count > buf_size)
    {
      /* cesu-8 string breaks in the middle */
      return false;
    }

    for (lit_utf8_size_t offset = 0; offset < extra_bytes_count; ++offset)
    {
      c = cesu8_buf_p[idx + offset];
      if ((c & LIT_UTF8_EXTRA_BYTE_MASK) != LIT_UTF8_EXTRA_BYTE_MARKER)
      {
        /* invalid continuation byte */
        return false;
      }
      code_point <<= LIT_UTF8_BITS_IN_EXTRA_BYTES;
      code_point |= (c & LIT_UTF8_LAST_6_BITS_MASK);
    }

    if (code_point < min_code_point)
    {
      /* cesu-8 string doesn't encode valid unicode code point */
      return false;
    }

    idx += extra_bytes_count;
  }

  return true;
}