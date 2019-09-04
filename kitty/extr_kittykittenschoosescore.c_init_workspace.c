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
typedef  int /*<<< orphan*/  text_t ;
typedef  size_t len_t ;
struct TYPE_4__ {int needle_len; int max_haystack_len; scalar_t__* needle; size_t** positions; size_t haystack_len; double max_score_per_char; int /*<<< orphan*/ * haystack; int /*<<< orphan*/ * positions_count; int /*<<< orphan*/ * level_factors; } ;
typedef  TYPE_1__ WorkSpace ;

/* Variables and functions */
 scalar_t__ LOWERCASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  level_factor_for (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
init_workspace(WorkSpace *w, text_t *haystack, len_t haystack_len) {
    // Calculate the positions and level_factors arrays for the specified haystack
    bool level_factor_calculated = false;
    memset(w->positions_count, 0, sizeof(*(w->positions_count)) * 2 * w->needle_len);
    memset(w->level_factors, 0, sizeof(*(w->level_factors)) * w->max_haystack_len);
    for (len_t i = 0; i < haystack_len; i++) {
        level_factor_calculated = false;
        for (len_t j = 0; j < w->needle_len; j++) {
            if (w->needle[j] == LOWERCASE(haystack[i])) {
                if (!level_factor_calculated) {
                    level_factor_calculated = true;
                    w->level_factors[i] = i > 0 ? level_factor_for(haystack[i], haystack[i-1], w) : 0;
                }
                w->positions[j][w->positions_count[j]++] = i;
            }
        }
    }
    w->haystack = haystack;
    w->haystack_len = haystack_len;
    w->max_score_per_char = (1.0 / haystack_len + 1.0 / w->needle_len) / 2.0;
}