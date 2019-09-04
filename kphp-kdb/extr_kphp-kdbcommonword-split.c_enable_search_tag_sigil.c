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

/* Variables and functions */
 int /*<<< orphan*/  declare_sigil (int) ; 
 int /*<<< orphan*/  sigil_word_detect ; 
 int /*<<< orphan*/  std_sigil_word_detect ; 

void enable_search_tag_sigil (void) {
  declare_sigil (0x1f);
  sigil_word_detect = std_sigil_word_detect;
}