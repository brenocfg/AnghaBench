#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ fullscreen_mode; scalar_t__ type; struct TYPE_7__* parent; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 scalar_t__ CF_NONE ; 
 scalar_t__ CF_OUTPUT ; 
 scalar_t__ CT_WORKSPACE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ con_get_workspace (TYPE_1__*) ; 
 int con_has_parent (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* focused ; 

bool con_fullscreen_permits_focusing(Con *con) {
    /* No focus, no problem. */
    if (!focused)
        return true;

    /* Find the first fullscreen ascendent. */
    Con *fs = focused;
    while (fs && fs->fullscreen_mode == CF_NONE)
        fs = fs->parent;

    /* fs must be non-NULL since the workspace con doesn’t have CF_NONE and
     * there always has to be a workspace con in the hierarchy. */
    assert(fs != NULL);
    /* The most common case is we hit the workspace level. In this
     * situation, changing focus is also harmless. */
    assert(fs->fullscreen_mode != CF_NONE);
    if (fs->type == CT_WORKSPACE)
        return true;

    /* Allow it if the container itself is the fullscreen container. */
    if (con == fs)
        return true;

    /* If fullscreen is per-output, the focus being in a different workspace is
     * sufficient to guarantee that change won't leave fullscreen in bad shape. */
    if (fs->fullscreen_mode == CF_OUTPUT &&
        con_get_workspace(con) != con_get_workspace(fs)) {
        return true;
    }

    /* Allow it only if the container to be focused is contained within the
     * current fullscreen container. */
    return con_has_parent(con, fs);
}