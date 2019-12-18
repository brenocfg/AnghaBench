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
typedef  void* uint8_t ;
typedef  int ecma_char_t ;

/* Variables and functions */
 int LIT_UTF8_1_BYTE_CODE_POINT_MAX ; 
 int LIT_UTF8_2_BYTE_CODE_POINT_MAX ; 
 int LIT_UTF8_2_BYTE_MARKER ; 
 int LIT_UTF8_3_BYTE_MARKER ; 
 int LIT_UTF8_EXTRA_BYTE_MARKER ; 
 int LIT_UTF8_LAST_4_BITS_MASK ; 
 int LIT_UTF8_LAST_5_BITS_MASK ; 
 int LIT_UTF8_LAST_6_BITS_MASK ; 

size_t
lit_char_to_utf8_bytes (uint8_t *dst_p, /**< destination buffer */
                        ecma_char_t chr) /**< EcmaScript character */
{
  if (!(chr & ~LIT_UTF8_1_BYTE_CODE_POINT_MAX))
  {
    /* 00000000 0xxxxxxx -> 0xxxxxxx */
    *dst_p = (uint8_t) chr;
    return 1;
  }

  if (!(chr & ~LIT_UTF8_2_BYTE_CODE_POINT_MAX))
  {
    /* 00000yyy yyxxxxxx -> 110yyyyy 10xxxxxx */
    *(dst_p++) = (uint8_t) (LIT_UTF8_2_BYTE_MARKER | ((chr >> 6) & LIT_UTF8_LAST_5_BITS_MASK));
    *dst_p = (uint8_t) (LIT_UTF8_EXTRA_BYTE_MARKER | (chr & LIT_UTF8_LAST_6_BITS_MASK));
    return 2;
  }

  /* zzzzyyyy yyxxxxxx -> 1110zzzz 10yyyyyy 10xxxxxx */
  *(dst_p++) = (uint8_t) (LIT_UTF8_3_BYTE_MARKER | ((chr >> 12) & LIT_UTF8_LAST_4_BITS_MASK));
  *(dst_p++) = (uint8_t) (LIT_UTF8_EXTRA_BYTE_MARKER | ((chr >> 6) & LIT_UTF8_LAST_6_BITS_MASK));
  *dst_p = (uint8_t) (LIT_UTF8_EXTRA_BYTE_MARKER | (chr & LIT_UTF8_LAST_6_BITS_MASK));
  return 3;
}