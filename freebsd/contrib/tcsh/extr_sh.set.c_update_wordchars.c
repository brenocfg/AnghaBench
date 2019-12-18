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
 scalar_t__ STR_WORD_CHARS ; 
 scalar_t__ STR_WORD_CHARS_VI ; 
 scalar_t__ VImode ; 
 scalar_t__ word_chars ; 

void
update_wordchars(void)
{
    if ((word_chars == STR_WORD_CHARS) || (word_chars == STR_WORD_CHARS_VI)) {
	word_chars = (VImode ? STR_WORD_CHARS_VI : STR_WORD_CHARS);
    }
}