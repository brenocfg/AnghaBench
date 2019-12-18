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
typedef  scalar_t__ direction_t ;
typedef  int /*<<< orphan*/  Output ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSEST_OUTPUT ; 
 int /*<<< orphan*/  DLOG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ D_DOWN ; 
 scalar_t__ D_LEFT ; 
 scalar_t__ D_RIGHT ; 
 scalar_t__ D_UP ; 
 int /*<<< orphan*/  FARTHEST_OUTPUT ; 
 int /*<<< orphan*/ * get_output_next (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_primary_name (int /*<<< orphan*/ *) ; 

Output *get_output_next_wrap(direction_t direction, Output *current) {
    Output *best = get_output_next(direction, current, CLOSEST_OUTPUT);
    /* If no output can be found, wrap */
    if (!best) {
        direction_t opposite;
        if (direction == D_RIGHT)
            opposite = D_LEFT;
        else if (direction == D_LEFT)
            opposite = D_RIGHT;
        else if (direction == D_DOWN)
            opposite = D_UP;
        else
            opposite = D_DOWN;
        best = get_output_next(opposite, current, FARTHEST_OUTPUT);
    }
    if (!best)
        best = current;
    DLOG("current = %s, best = %s\n", output_primary_name(current), output_primary_name(best));
    return best;
}