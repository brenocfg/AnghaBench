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
typedef  int /*<<< orphan*/  utf8_char_size ;
typedef  scalar_t__ lit_utf8_size_t ;
typedef  int /*<<< orphan*/  lit_utf8_byte_t ;
typedef  scalar_t__ ecma_length_t ;

/* Variables and functions */
 int /*<<< orphan*/  CESU8_ANY_SIZE ; 
 scalar_t__ LIT_CESU8_MAX_BYTES_IN_CODE_UNIT ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 scalar_t__ generate_cesu8_char (int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 
 int lit_is_valid_cesu8_string (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static ecma_length_t
generate_cesu8_string (lit_utf8_byte_t *buf_p,
                       lit_utf8_size_t buf_size)
{
  ecma_length_t length = 0;

  lit_utf8_size_t size = 0;
  while (size  < buf_size)
  {
    const utf8_char_size char_size = (((buf_size - size) > LIT_CESU8_MAX_BYTES_IN_CODE_UNIT)
                                      ? CESU8_ANY_SIZE
                                      : (utf8_char_size) (buf_size - size));

    lit_utf8_size_t bytes_generated = generate_cesu8_char (char_size, buf_p);

    TEST_ASSERT (lit_is_valid_cesu8_string (buf_p, bytes_generated));

    size += bytes_generated;
    buf_p += bytes_generated;
    length++;
  }

  TEST_ASSERT (size == buf_size);

  return length;
}