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
typedef  size_t len_t ;
struct TYPE_3__ {size_t needle_len; scalar_t__* positions_count; int** positions; } ;
typedef  TYPE_1__ WorkSpace ;

/* Variables and functions */

__attribute__((used)) static inline bool
has_atleast_one_match(WorkSpace *w) {
    int p = -1;
    bool found;
    for (len_t i = 0; i < w->needle_len; i++) {
        if (w->positions_count[i] == 0) return false;  // All characters of the needle are not present in the haystack
        found = false;
        for (len_t j = 0; j < w->positions_count[i]; j++) {
            if (w->positions[i][j] > p) { p = w->positions[i][j]; found = true; break; }
        }
        if (!found) return false; // Characters of needle not present in sequence in haystack
    }
    return true;
}