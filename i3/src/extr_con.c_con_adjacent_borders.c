#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  adjacent_t ;
struct TYPE_7__ {scalar_t__ x; scalar_t__ width; scalar_t__ y; scalar_t__ height; } ;
struct TYPE_8__ {TYPE_1__ rect; } ;
typedef  TYPE_2__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  ADJ_LEFT_SCREEN_EDGE ; 
 int /*<<< orphan*/  ADJ_LOWER_SCREEN_EDGE ; 
 int /*<<< orphan*/  ADJ_NONE ; 
 int /*<<< orphan*/  ADJ_RIGHT_SCREEN_EDGE ; 
 int /*<<< orphan*/  ADJ_UPPER_SCREEN_EDGE ; 
 TYPE_2__* con_get_workspace (TYPE_2__*) ; 
 scalar_t__ con_is_floating (TYPE_2__*) ; 

adjacent_t con_adjacent_borders(Con *con) {
    adjacent_t result = ADJ_NONE;
    /* Floating windows are never adjacent to any other window, so
       don’t hide their border(s). This prevents bug #998. */
    if (con_is_floating(con))
        return result;

    Con *workspace = con_get_workspace(con);
    if (con->rect.x == workspace->rect.x)
        result |= ADJ_LEFT_SCREEN_EDGE;
    if (con->rect.x + con->rect.width == workspace->rect.x + workspace->rect.width)
        result |= ADJ_RIGHT_SCREEN_EDGE;
    if (con->rect.y == workspace->rect.y)
        result |= ADJ_UPPER_SCREEN_EDGE;
    if (con->rect.y + con->rect.height == workspace->rect.y + workspace->rect.height)
        result |= ADJ_LOWER_SCREEN_EDGE;
    return result;
}