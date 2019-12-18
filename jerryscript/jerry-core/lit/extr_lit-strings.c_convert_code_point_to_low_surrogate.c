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
typedef  int lit_code_point_t ;
typedef  int ecma_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 int LIT_UTF16_CODE_UNIT_MAX ; 
 int LIT_UTF16_LAST_10_BITS_MASK ; 
 int LIT_UTF16_LOW_SURROGATE_MARKER ; 

__attribute__((used)) static ecma_char_t
convert_code_point_to_low_surrogate (lit_code_point_t code_point) /**< code point, should be > 0xFFFF */
{
  JERRY_ASSERT (code_point > LIT_UTF16_CODE_UNIT_MAX);

  ecma_char_t code_unit_bits;
  code_unit_bits = (ecma_char_t) (code_point & LIT_UTF16_LAST_10_BITS_MASK);

  return (ecma_char_t) (LIT_UTF16_LOW_SURROGATE_MARKER | code_unit_bits);
}