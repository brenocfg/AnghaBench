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
typedef  scalar_t__ lit_utf8_size_t ;
typedef  int /*<<< orphan*/  lit_utf8_byte_t ;
typedef  scalar_t__ ecma_length_t ;
typedef  int /*<<< orphan*/  ecma_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 int /*<<< orphan*/  lit_is_code_point_utf16_high_surrogate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lit_is_code_point_utf16_low_surrogate (int /*<<< orphan*/ ) ; 
 scalar_t__ lit_read_code_unit_from_utf8 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

ecma_length_t
lit_get_utf8_length_of_cesu8_string (const lit_utf8_byte_t *cesu8_buf_p, /**< cesu-8 string */
                                     lit_utf8_size_t cesu8_buf_size) /**< string size */
{
  lit_utf8_size_t offset = 0;
  ecma_length_t utf8_length = 0;
  ecma_char_t prev_ch = 0;

  while (offset < cesu8_buf_size)
  {
    ecma_char_t ch;
    offset += lit_read_code_unit_from_utf8 (cesu8_buf_p + offset, &ch);

    if (!lit_is_code_point_utf16_low_surrogate (ch) || !lit_is_code_point_utf16_high_surrogate (prev_ch))
    {
      utf8_length++;
    }

    prev_ch = ch;
  }

  JERRY_ASSERT (offset == cesu8_buf_size);

  return utf8_length;
}