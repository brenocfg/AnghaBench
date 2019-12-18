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
typedef  char uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_INIT () ; 
 int /*<<< orphan*/  ecma_finalize () ; 
 int /*<<< orphan*/  ecma_init () ; 
 int /*<<< orphan*/  jmem_finalize () ; 
 int /*<<< orphan*/  jmem_init () ; 
 int /*<<< orphan*/  lexer_hex_to_character (int /*<<< orphan*/ ,char const*,int) ; 
 size_t lit_char_get_utf8_length (int /*<<< orphan*/ ) ; 

int
main (void)
{
  TEST_INIT ();

  jmem_init ();
  ecma_init ();

  const uint8_t _1_byte_long1[] = "\\u007F";
  const uint8_t _1_byte_long2[] = "\\u0000";
  const uint8_t _1_byte_long3[] = "\\u0065";

  const uint8_t _2_byte_long1[] = "\\u008F";
  const uint8_t _2_byte_long2[] = "\\u00FF";
  const uint8_t _2_byte_long3[] = "\\u07FF";

  const uint8_t _3_byte_long1[] = "\\u08FF";
  const uint8_t _3_byte_long2[] = "\\u0FFF";
  const uint8_t _3_byte_long3[] = "\\uFFFF";

  size_t length;

  /* Test 1-byte-long unicode sequences. */
  length = lit_char_get_utf8_length (lexer_hex_to_character (0, _1_byte_long1 + 2, 4));
  TEST_ASSERT (length == 1);

  length = lit_char_get_utf8_length (lexer_hex_to_character (0, _1_byte_long2 + 2, 4));
  TEST_ASSERT (length == 1);

  length = lit_char_get_utf8_length (lexer_hex_to_character (0, _1_byte_long3 + 2, 4));
  TEST_ASSERT (length == 1);

  /* Test 2-byte-long unicode sequences. */
  length = lit_char_get_utf8_length (lexer_hex_to_character (0, _2_byte_long1 + 2, 4));
  TEST_ASSERT (length == 2);

  length = lit_char_get_utf8_length (lexer_hex_to_character (0, _2_byte_long2 + 2, 4));
  TEST_ASSERT (length == 2);

  length = lit_char_get_utf8_length (lexer_hex_to_character (0, _2_byte_long3 + 2, 4));
  TEST_ASSERT (length == 2);

  /* Test 3-byte-long unicode sequences. */
  length = lit_char_get_utf8_length (lexer_hex_to_character (0, _3_byte_long1 + 2, 4));
  TEST_ASSERT (length != 2);

  length = lit_char_get_utf8_length (lexer_hex_to_character (0, _3_byte_long2 + 2, 4));
  TEST_ASSERT (length == 3);

  length = lit_char_get_utf8_length (lexer_hex_to_character (0, _3_byte_long3 + 2, 4));
  TEST_ASSERT (length == 3);

  ecma_finalize ();
  jmem_finalize ();

  return 0;
}