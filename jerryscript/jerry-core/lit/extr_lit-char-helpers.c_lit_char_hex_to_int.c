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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ ecma_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ LIT_CHAR_ASCII_DIGITS_BEGIN ; 
 scalar_t__ LIT_CHAR_ASCII_DIGITS_END ; 
 scalar_t__ LIT_CHAR_ASCII_LOWERCASE_LETTERS_HEX_BEGIN ; 
 scalar_t__ LIT_CHAR_ASCII_LOWERCASE_LETTERS_HEX_END ; 
 scalar_t__ LIT_CHAR_ASCII_UPPERCASE_LETTERS_HEX_BEGIN ; 
 int /*<<< orphan*/  lit_char_is_hex_digit (scalar_t__) ; 

uint32_t
lit_char_hex_to_int (ecma_char_t c) /**< code unit, corresponding to
                                     *    one of HexDigit characters */
{
  JERRY_ASSERT (lit_char_is_hex_digit (c));

  if (c >= LIT_CHAR_ASCII_DIGITS_BEGIN && c <= LIT_CHAR_ASCII_DIGITS_END)
  {
    return (uint32_t) (c - LIT_CHAR_ASCII_DIGITS_BEGIN);
  }
  else if (c >= LIT_CHAR_ASCII_LOWERCASE_LETTERS_HEX_BEGIN && c <= LIT_CHAR_ASCII_LOWERCASE_LETTERS_HEX_END)
  {
    return (uint32_t) (c - LIT_CHAR_ASCII_LOWERCASE_LETTERS_HEX_BEGIN + 10);
  }
  else
  {
    return (uint32_t) (c - LIT_CHAR_ASCII_UPPERCASE_LETTERS_HEX_BEGIN + 10);
  }
}