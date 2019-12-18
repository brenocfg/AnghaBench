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
typedef  int /*<<< orphan*/  ecma_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  NUM_OF_ELEMENTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lit_unicode_letter_chars ; 
 int /*<<< orphan*/  lit_unicode_letter_interval_lengths ; 
 int /*<<< orphan*/  lit_unicode_letter_interval_sps ; 
 scalar_t__ search_char_in_char_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ search_char_in_interval_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
lit_char_is_unicode_letter (ecma_char_t c) /**< code unit */
{
  return (search_char_in_interval_array (c,
                                         lit_unicode_letter_interval_sps,
                                         lit_unicode_letter_interval_lengths,
                                         NUM_OF_ELEMENTS (lit_unicode_letter_interval_sps))
          || search_char_in_char_array (c, lit_unicode_letter_chars, NUM_OF_ELEMENTS (lit_unicode_letter_chars)));
}