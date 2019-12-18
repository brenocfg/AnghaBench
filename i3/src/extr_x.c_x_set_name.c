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
struct con_state {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ frame; } ;
typedef  TYPE_2__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  ELOG (char*) ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sstrdup (char const*) ; 
 struct con_state* state_for_frame (int /*<<< orphan*/ ) ; 

void x_set_name(Con *con, const char *name) {
    struct con_state *state;

    if ((state = state_for_frame(con->frame.id)) == NULL) {
        ELOG("window state not found\n");
        return;
    }

    FREE(state->name);
    state->name = sstrdup(name);
}