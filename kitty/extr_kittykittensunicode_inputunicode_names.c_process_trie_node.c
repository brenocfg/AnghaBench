#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t children_offset; scalar_t__ match_offset; } ;
typedef  TYPE_1__ word_trie ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  char_type ;

/* Variables and functions */
 int /*<<< orphan*/  add_matches (TYPE_1__ const*,int /*<<< orphan*/ *,size_t*,size_t const) ; 
 TYPE_1__* all_trie_nodes ; 
 void** children_array ; 

__attribute__((used)) static void
process_trie_node(const word_trie *wt, char_type *codepoints, size_t *pos, const size_t sz) {
    if (wt->match_offset) add_matches(wt, codepoints, pos, sz);
    size_t num_children = children_array[wt->children_offset];
    if (!num_children) return;
    for (size_t c = wt->children_offset + 1; c < wt->children_offset + 1 + num_children; c++) {
        if (*pos > sz) return;
        uint32_t x = children_array[c];
        process_trie_node(&all_trie_nodes[x >> 8], codepoints, pos, sz);
    }
}