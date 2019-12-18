#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fullscreen_mode_t ;
struct TYPE_13__ {scalar_t__ type; int /*<<< orphan*/  name; int /*<<< orphan*/  fullscreen_mode; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  CF_GLOBAL ; 
 int /*<<< orphan*/  CF_OUTPUT ; 
 scalar_t__ CT_WORKSPACE ; 
 int /*<<< orphan*/  DLOG (char*,...) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  con_activate (TYPE_1__*) ; 
 int /*<<< orphan*/  con_disable_fullscreen (TYPE_1__*) ; 
 TYPE_1__* con_get_fullscreen_con (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* con_get_workspace (TYPE_1__*) ; 
 int /*<<< orphan*/  con_set_fullscreen_mode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* croot ; 
 TYPE_1__* focused ; 
 int /*<<< orphan*/  workspace_show (TYPE_1__*) ; 

void con_enable_fullscreen(Con *con, fullscreen_mode_t fullscreen_mode) {
    if (con->type == CT_WORKSPACE) {
        DLOG("You cannot make a workspace fullscreen.\n");
        return;
    }

    assert(fullscreen_mode == CF_GLOBAL || fullscreen_mode == CF_OUTPUT);

    if (fullscreen_mode == CF_GLOBAL)
        DLOG("enabling global fullscreen for %p / %s\n", con, con->name);
    else
        DLOG("enabling fullscreen for %p / %s\n", con, con->name);

    if (con->fullscreen_mode == fullscreen_mode) {
        DLOG("fullscreen already enabled for %p / %s\n", con, con->name);
        return;
    }

    Con *con_ws = con_get_workspace(con);

    /* Disable any fullscreen container that would conflict the new one. */
    Con *fullscreen = con_get_fullscreen_con(croot, CF_GLOBAL);
    if (fullscreen == NULL)
        fullscreen = con_get_fullscreen_con(con_ws, CF_OUTPUT);
    if (fullscreen != NULL)
        con_disable_fullscreen(fullscreen);

    /* Set focus to new fullscreen container. Unless in global fullscreen mode
     * and on another workspace restore focus afterwards.
     * Switch to the container’s workspace if mode is global. */
    Con *cur_ws = con_get_workspace(focused);
    Con *old_focused = focused;
    if (fullscreen_mode == CF_GLOBAL && cur_ws != con_ws)
        workspace_show(con_ws);
    con_activate(con);
    if (fullscreen_mode != CF_GLOBAL && cur_ws != con_ws)
        con_activate(old_focused);

    con_set_fullscreen_mode(con, fullscreen_mode);
}