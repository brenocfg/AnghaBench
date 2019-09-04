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
typedef  scalar_t__ char_type ;

/* Variables and functions */
 scalar_t__ OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * select_by_word_characters ; 
 int /*<<< orphan*/  select_by_word_characters_count ; 

__attribute__((used)) static inline bool
is_opt_word_char(char_type ch) {
    for (size_t i = 0; i < OPT(select_by_word_characters_count); i++) {
        if (OPT(select_by_word_characters[i]) == ch) return true;
    }
    return false;
}