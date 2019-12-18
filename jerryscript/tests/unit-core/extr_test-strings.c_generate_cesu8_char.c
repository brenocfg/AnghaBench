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
typedef  int utf8_char_size ;
typedef  int /*<<< orphan*/  lit_utf8_size_t ;
typedef  int /*<<< orphan*/  lit_utf8_byte_t ;
typedef  int lit_code_point_t ;
typedef  int /*<<< orphan*/  ecma_char_t ;

/* Variables and functions */
 int LIT_CESU8_MAX_BYTES_IN_CODE_UNIT ; 
 int LIT_UTF16_HIGH_SURROGATE_MIN ; 
 int LIT_UTF16_LOW_SURROGATE_MAX ; 
 int LIT_UTF8_1_BYTE_CODE_POINT_MAX ; 
 int LIT_UTF8_2_BYTE_CODE_POINT_MAX ; 
 int LIT_UTF8_2_BYTE_CODE_POINT_MIN ; 
 int LIT_UTF8_3_BYTE_CODE_POINT_MAX ; 
 int LIT_UTF8_3_BYTE_CODE_POINT_MIN ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  lit_code_unit_to_utf8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rand () ; 

__attribute__((used)) static lit_utf8_size_t
generate_cesu8_char (utf8_char_size char_size,
                     lit_utf8_byte_t *buf)
{
  TEST_ASSERT (char_size >= 0 && char_size <= LIT_CESU8_MAX_BYTES_IN_CODE_UNIT);
  lit_code_point_t code_point = (lit_code_point_t) rand ();

  if (char_size == 1)
  {
    code_point %= LIT_UTF8_1_BYTE_CODE_POINT_MAX;
  }
  else if (char_size == 2)
  {
    code_point = LIT_UTF8_2_BYTE_CODE_POINT_MIN + code_point % (LIT_UTF8_2_BYTE_CODE_POINT_MAX -
                                                                LIT_UTF8_2_BYTE_CODE_POINT_MIN);
  }
  else if (char_size == 3)
  {
    code_point = LIT_UTF8_3_BYTE_CODE_POINT_MIN + code_point % (LIT_UTF8_3_BYTE_CODE_POINT_MAX -
                                                                LIT_UTF8_3_BYTE_CODE_POINT_MIN);
  }
  else
  {
    code_point %= LIT_UTF8_3_BYTE_CODE_POINT_MAX;
  }

  if (code_point >= LIT_UTF16_HIGH_SURROGATE_MIN
      && code_point <= LIT_UTF16_LOW_SURROGATE_MAX)
  {
    code_point = LIT_UTF16_HIGH_SURROGATE_MIN - 1;
  }

  return lit_code_unit_to_utf8 ((ecma_char_t) code_point, buf);
}