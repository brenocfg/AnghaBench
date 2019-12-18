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
typedef  int ecma_char_t ;

/* Variables and functions */
 int LIT_UTF8_1_BYTE_CODE_POINT_MAX ; 
 int LIT_UTF8_2_BYTE_CODE_POINT_MAX ; 

size_t
lit_char_get_utf8_length (ecma_char_t chr) /**< EcmaScript character */
{
  if (!(chr & ~LIT_UTF8_1_BYTE_CODE_POINT_MAX))
  {
    /* 00000000 0xxxxxxx */
    return 1;
  }

  if (!(chr & ~LIT_UTF8_2_BYTE_CODE_POINT_MAX))
  {
    /* 00000yyy yyxxxxxx */
    return 2;
  }

  /* zzzzyyyy yyxxxxxx */
  return 3;
}