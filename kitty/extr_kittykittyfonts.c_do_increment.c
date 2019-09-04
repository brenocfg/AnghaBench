#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ x; scalar_t__ xnum; scalar_t__ y; scalar_t__ max_y; int /*<<< orphan*/  z; int /*<<< orphan*/  ynum; } ;
struct TYPE_5__ {TYPE_1__ sprite_tracker; } ;
typedef  TYPE_2__ FontGroup ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  UINT16_MAX ; 
 scalar_t__ max_array_len ; 

__attribute__((used)) static inline void
do_increment(FontGroup *fg, int *error) {
    fg->sprite_tracker.x++;
    if (fg->sprite_tracker.x >= fg->sprite_tracker.xnum) {
        fg->sprite_tracker.x = 0; fg->sprite_tracker.y++;
        fg->sprite_tracker.ynum = MIN(MAX(fg->sprite_tracker.ynum, fg->sprite_tracker.y + 1), fg->sprite_tracker.max_y);
        if (fg->sprite_tracker.y >= fg->sprite_tracker.max_y) {
            fg->sprite_tracker.y = 0; fg->sprite_tracker.z++;
            if (fg->sprite_tracker.z >= MIN(UINT16_MAX, max_array_len)) *error = 2;
        }
    }
}