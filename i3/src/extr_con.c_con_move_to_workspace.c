#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ type; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 scalar_t__ CT_WORKSPACE ; 
 int /*<<< orphan*/  DLOG (char*) ; 
 int /*<<< orphan*/  _con_move_to_con (TYPE_1__*,TYPE_1__*,int,int,int,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* con_descend_focused (TYPE_1__*) ; 
 TYPE_1__* con_get_workspace (TYPE_1__*) ; 

void con_move_to_workspace(Con *con, Con *workspace, bool fix_coordinates, bool dont_warp, bool ignore_focus) {
    assert(workspace->type == CT_WORKSPACE);

    Con *source_ws = con_get_workspace(con);
    if (workspace == source_ws) {
        DLOG("Not moving, already there\n");
        return;
    }

    Con *target = con_descend_focused(workspace);
    _con_move_to_con(con, target, true, fix_coordinates, dont_warp, ignore_focus, true);
}