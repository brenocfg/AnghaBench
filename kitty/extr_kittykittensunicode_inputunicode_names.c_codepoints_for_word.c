#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t children_offset; } ;
typedef  TYPE_1__ word_trie ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  char_type ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyFrozenSet_New (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyLong_FromUnsignedLong (int /*<<< orphan*/ ) ; 
 int PySet_Add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 TYPE_1__* all_trie_nodes ; 
 int /*<<< orphan*/  arraysz (int /*<<< orphan*/ *) ; 
 void** children_array ; 
 int /*<<< orphan*/  process_trie_node (TYPE_1__ const*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline PyObject*
codepoints_for_word(const char *word, size_t len) {
    const word_trie *wt = all_trie_nodes;
    for (size_t i = 0; i < len; i++) {
        unsigned char ch = word[i];
        size_t num_children = children_array[wt->children_offset];
        if (!num_children) return PyFrozenSet_New(NULL);
        bool found = false;
        for (size_t c = wt->children_offset + 1; c < wt->children_offset + 1 + num_children; c++) {
            uint32_t x = children_array[c];
            if ((x & 0xff) == ch) {
                found = true;
                wt = &all_trie_nodes[x >> 8];
                break;
            }
        }
        if (!found) return PyFrozenSet_New(NULL);
    }
    static char_type codepoints[1024];
    size_t cpos = 0;
    process_trie_node(wt, codepoints, &cpos, arraysz(codepoints));
    PyObject *ans = PyFrozenSet_New(NULL); if (ans == NULL) return NULL;
    for (size_t i = 0; i < cpos; i++) {
        PyObject *t = PyLong_FromUnsignedLong(codepoints[i]); if (t == NULL) { Py_DECREF(ans); return NULL; }
        int ret = PySet_Add(ans, t); Py_DECREF(t); if (ret != 0) { Py_DECREF(ans); return NULL; }
    }
    return ans;
}