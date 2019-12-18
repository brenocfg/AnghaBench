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
typedef  scalar_t__ ecma_char_t ;

/* Variables and functions */
 scalar_t__ LEXER_TO_ASCII_LOWERCASE (scalar_t__) ; 
 scalar_t__ LIT_CHAR_ASCII_DIGITS_BEGIN ; 
 scalar_t__ LIT_CHAR_ASCII_DIGITS_END ; 
 scalar_t__ LIT_CHAR_ASCII_LOWERCASE_LETTERS_HEX_BEGIN ; 
 scalar_t__ LIT_CHAR_ASCII_LOWERCASE_LETTERS_HEX_END ; 

bool
lit_char_is_hex_digit (ecma_char_t c) /**< code unit */
{
  return ((c >= LIT_CHAR_ASCII_DIGITS_BEGIN && c <= LIT_CHAR_ASCII_DIGITS_END)
          || (LEXER_TO_ASCII_LOWERCASE (c) >= LIT_CHAR_ASCII_LOWERCASE_LETTERS_HEX_BEGIN
              && LEXER_TO_ASCII_LOWERCASE (c) <= LIT_CHAR_ASCII_LOWERCASE_LETTERS_HEX_END));
}