#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t match_offset; } ;
typedef  TYPE_1__ word_trie ;
typedef  int /*<<< orphan*/  char_type ;

/* Variables and functions */
 size_t* mark_groups ; 
 int /*<<< orphan*/ * mark_to_cp ; 

__attribute__((used)) static inline void
add_matches(const word_trie *wt, char_type *codepoints, size_t *pos, const size_t sz) {
    size_t num = mark_groups[wt->match_offset];
    for (size_t i = wt->match_offset + 1; i < wt->match_offset + 1 + num && *pos < sz; i++, (*pos)++) {
        codepoints[*pos] = mark_to_cp[mark_groups[i]];
    }
}