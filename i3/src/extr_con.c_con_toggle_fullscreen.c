#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; scalar_t__ fullscreen_mode; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 scalar_t__ CF_NONE ; 
 scalar_t__ CT_WORKSPACE ; 
 int /*<<< orphan*/  DLOG (char*,...) ; 
 int /*<<< orphan*/  con_disable_fullscreen (TYPE_1__*) ; 
 int /*<<< orphan*/  con_enable_fullscreen (TYPE_1__*,int) ; 

void con_toggle_fullscreen(Con *con, int fullscreen_mode) {
    if (con->type == CT_WORKSPACE) {
        DLOG("You cannot make a workspace fullscreen.\n");
        return;
    }

    DLOG("toggling fullscreen for %p / %s\n", con, con->name);

    if (con->fullscreen_mode == CF_NONE)
        con_enable_fullscreen(con, fullscreen_mode);
    else
        con_disable_fullscreen(con);
}