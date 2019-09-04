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
typedef  scalar_t__ len_t ;
struct TYPE_3__ {scalar_t__ needle_len; double max_score_per_char; int* level_factors; } ;
typedef  TYPE_1__ WorkSpace ;

/* Variables and functions */
 scalar_t__ LEN_MAX ; 
 scalar_t__ POSITION (scalar_t__) ; 

__attribute__((used)) static inline double
calc_score(WorkSpace *w) {
    double ans = 0;
    len_t distance, pos;
    for (len_t i = 0; i < w->needle_len; i++) {
        pos = POSITION(i);
        if (i == 0) distance = pos < LEN_MAX ? pos + 1 : LEN_MAX;
        else {
            distance = pos - POSITION(i-1);
            if (distance < 2) {
                ans += w->max_score_per_char; // consecutive characters
                continue;
            }
        }
        if (w->level_factors[pos]) ans += (100 * w->max_score_per_char) / w->level_factors[pos];  // at a special location
        else ans += (0.75 * w->max_score_per_char) / distance;
    }
    return ans;
}