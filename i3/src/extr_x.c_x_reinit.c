#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct con_state {int initial; int child_mapped; int /*<<< orphan*/  window_rect; TYPE_2__* con; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ frame; } ;
typedef  int /*<<< orphan*/  Rect ;
typedef  TYPE_2__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,struct con_state*) ; 
 int /*<<< orphan*/  ELOG (char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct con_state* state_for_frame (int /*<<< orphan*/ ) ; 

void x_reinit(Con *con) {
    struct con_state *state;

    if ((state = state_for_frame(con->frame.id)) == NULL) {
        ELOG("window state not found\n");
        return;
    }

    DLOG("resetting state %p to initial\n", state);
    state->initial = true;
    state->child_mapped = false;
    state->con = con;
    memset(&(state->window_rect), 0, sizeof(Rect));
}