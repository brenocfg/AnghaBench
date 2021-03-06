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
typedef  int /*<<< orphan*/  position_t ;
typedef  scalar_t__ direction_t ;

/* Variables and functions */
 int /*<<< orphan*/  AFTER ; 
 int /*<<< orphan*/  BEFORE ; 
 scalar_t__ D_LEFT ; 
 scalar_t__ D_UP ; 

position_t position_from_direction(direction_t direction) {
    return (direction == D_LEFT || direction == D_UP) ? BEFORE : AFTER;
}