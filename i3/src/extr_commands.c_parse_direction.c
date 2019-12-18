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
typedef  int /*<<< orphan*/  direction_t ;

/* Variables and functions */
 int /*<<< orphan*/  D_DOWN ; 
 int /*<<< orphan*/  D_LEFT ; 
 int /*<<< orphan*/  D_RIGHT ; 
 int /*<<< orphan*/  D_UP ; 
 int /*<<< orphan*/  ELOG (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static direction_t parse_direction(const char *str) {
    if (strcmp(str, "left") == 0) {
        return D_LEFT;
    } else if (strcmp(str, "right") == 0) {
        return D_RIGHT;
    } else if (strcmp(str, "up") == 0) {
        return D_UP;
    } else if (strcmp(str, "down") == 0) {
        return D_DOWN;
    } else {
        ELOG("Invalid direction. This is a parser bug.\n");
        assert(false);
    }
}