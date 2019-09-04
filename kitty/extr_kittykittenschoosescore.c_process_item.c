#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t len_t ;
struct TYPE_6__ {size_t needle_len; } ;
typedef  TYPE_1__ WorkSpace ;

/* Variables and functions */
 size_t POSITION (size_t) ; 
 int /*<<< orphan*/  address_is_monotonic (TYPE_1__*) ; 
 double calc_score (TYPE_1__*) ; 
 scalar_t__ increment_address (TYPE_1__*) ; 

__attribute__((used)) static double
process_item(WorkSpace *w, len_t *match_positions) {
    double highscore = 0, score;
    do {
        if (!address_is_monotonic(w)) continue;
        score = calc_score(w);
        if (score > highscore) {
            highscore = score;
            for (len_t i = 0; i < w->needle_len; i++) match_positions[i] = POSITION(i);
        }
    } while(increment_address(w));
    return highscore;
}