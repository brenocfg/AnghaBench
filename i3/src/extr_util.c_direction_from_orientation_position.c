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
typedef  scalar_t__ position_t ;
typedef  scalar_t__ orientation_t ;
typedef  int /*<<< orphan*/  direction_t ;

/* Variables and functions */
 scalar_t__ BEFORE ; 
 int /*<<< orphan*/  D_DOWN ; 
 int /*<<< orphan*/  D_LEFT ; 
 int /*<<< orphan*/  D_RIGHT ; 
 int /*<<< orphan*/  D_UP ; 
 scalar_t__ HORIZ ; 

direction_t direction_from_orientation_position(orientation_t orientation, position_t position) {
    if (orientation == HORIZ) {
        return position == BEFORE ? D_LEFT : D_RIGHT;
    } else {
        return position == BEFORE ? D_UP : D_DOWN;
    }
}