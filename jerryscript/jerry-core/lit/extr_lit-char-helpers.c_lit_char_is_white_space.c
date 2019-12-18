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
 scalar_t__ LIT_CHAR_BOM ; 
 scalar_t__ LIT_CHAR_FF ; 
 scalar_t__ LIT_CHAR_NBSP ; 
 scalar_t__ LIT_CHAR_SP ; 
 scalar_t__ LIT_CHAR_TAB ; 
 scalar_t__ LIT_CHAR_VTAB ; 
 scalar_t__ LIT_UTF8_1_BYTE_CODE_POINT_MAX ; 
 int /*<<< orphan*/  NUM_OF_ELEMENTS (int /*<<< orphan*/ ) ; 
 scalar_t__* lit_unicode_separator_char_interval_lengths ; 
 scalar_t__* lit_unicode_separator_char_interval_sps ; 
 int /*<<< orphan*/  lit_unicode_separator_chars ; 
 scalar_t__ search_char_in_char_array (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
lit_char_is_white_space (ecma_char_t c) /**< code unit */
{
  if (c <= LIT_UTF8_1_BYTE_CODE_POINT_MAX)
  {
    return (c == LIT_CHAR_TAB
            || c == LIT_CHAR_VTAB
            || c == LIT_CHAR_FF
            || c == LIT_CHAR_SP);
  }
  else
  {
    return (c == LIT_CHAR_NBSP
            || c == LIT_CHAR_BOM
            || (c >= lit_unicode_separator_char_interval_sps[0]
                && c <= lit_unicode_separator_char_interval_sps[0] + lit_unicode_separator_char_interval_lengths[0])
            || search_char_in_char_array (c,
                                          lit_unicode_separator_chars,
                                          NUM_OF_ELEMENTS (lit_unicode_separator_chars)));
  }
}