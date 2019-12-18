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
typedef  int /*<<< orphan*/  Con ;

/* Variables and functions */
 int /*<<< orphan*/  CF_GLOBAL ; 
 int /*<<< orphan*/  CF_OUTPUT ; 
 int /*<<< orphan*/ * con_get_fullscreen_con (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * con_get_workspace (int /*<<< orphan*/ *) ; 
 scalar_t__ con_has_parent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int resize_find_tiling_participants (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 

bool has_adjacent_container(Con *con, direction_t direction) {
    Con *workspace = con_get_workspace(con);
    Con *fullscreen = con_get_fullscreen_con(workspace, CF_GLOBAL);
    if (fullscreen == NULL)
        fullscreen = con_get_fullscreen_con(workspace, CF_OUTPUT);

    /* If this container is fullscreen by itself, there's no adjacent container. */
    if (con == fullscreen)
        return false;

    Con *first = con;
    Con *second = NULL;
    bool found_neighbor = resize_find_tiling_participants(&first, &second, direction, false);
    if (!found_neighbor)
        return false;

    /* If we have an adjacent container and nothing is fullscreen, we consider it. */
    if (fullscreen == NULL)
        return true;

    /* For fullscreen containers, only consider the adjacent container if it is also fullscreen. */
    return con_has_parent(con, fullscreen) && con_has_parent(second, fullscreen);
}