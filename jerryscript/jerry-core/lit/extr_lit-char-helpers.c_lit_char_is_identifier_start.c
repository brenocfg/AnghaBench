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
typedef  int uint8_t ;

/* Variables and functions */
 int const LIT_UTF8_1_BYTE_CODE_POINT_MAX ; 
 int const LIT_UTF8_4_BYTE_MARKER ; 
 int const LIT_UTF8_4_BYTE_MASK ; 
 int lit_char_is_identifier_start_character (int const) ; 
 int const lit_utf8_peek_next (int const*) ; 

bool
lit_char_is_identifier_start (const uint8_t *src_p) /**< pointer to a vaild UTF8 character */
{
  if (*src_p <= LIT_UTF8_1_BYTE_CODE_POINT_MAX)
  {
    return lit_char_is_identifier_start_character (*src_p);
  }

  /* ECMAScript 2015 specification allows some code points in supplementary plane.
   * However, we don't permit characters in supplementary characters as start of identifier.
   */
  if ((*src_p & LIT_UTF8_4_BYTE_MASK) == LIT_UTF8_4_BYTE_MARKER)
  {
    return false;
  }

  return lit_char_is_identifier_start_character (lit_utf8_peek_next (src_p));
}