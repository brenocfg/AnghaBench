#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_12__ {int urgent; TYPE_1__* window; int /*<<< orphan*/ * urgency_timer; } ;
struct TYPE_11__ {TYPE_5__ urgent; } ;
typedef  TYPE_2__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*) ; 
 int /*<<< orphan*/  LOG (char*,int const) ; 
 TYPE_2__* con_get_workspace (TYPE_2__*) ; 
 int /*<<< orphan*/  con_update_parents_urgency (TYPE_2__*) ; 
 TYPE_2__* focused ; 
 int /*<<< orphan*/  gettimeofday (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_send_window_event (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  workspace_update_urgent_flag (TYPE_2__*) ; 

void con_set_urgency(Con *con, bool urgent) {
    if (urgent && focused == con) {
        DLOG("Ignoring urgency flag for current client\n");
        return;
    }

    const bool old_urgent = con->urgent;

    if (con->urgency_timer == NULL) {
        con->urgent = urgent;
    } else
        DLOG("Discarding urgency WM_HINT because timer is running\n");

    //CLIENT_LOG(con);
    if (con->window) {
        if (con->urgent) {
            gettimeofday(&con->window->urgent, NULL);
        } else {
            con->window->urgent.tv_sec = 0;
            con->window->urgent.tv_usec = 0;
        }
    }

    con_update_parents_urgency(con);

    Con *ws;
    /* Set the urgency flag on the workspace, if a workspace could be found
     * (for dock clients, that is not the case). */
    if ((ws = con_get_workspace(con)) != NULL)
        workspace_update_urgent_flag(ws);

    if (con->urgent != old_urgent) {
        LOG("Urgency flag changed to %d\n", con->urgent);
        ipc_send_window_event("urgent", con);
    }
}