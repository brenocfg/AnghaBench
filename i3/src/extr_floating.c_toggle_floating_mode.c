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
struct TYPE_7__ {scalar_t__ type; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 scalar_t__ CT_FLOATING_CON ; 
 int /*<<< orphan*/  ELOG (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  LOG (char*) ; 
 scalar_t__ con_is_floating (TYPE_1__*) ; 
 int /*<<< orphan*/  floating_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  floating_enable (TYPE_1__*,int) ; 

void toggle_floating_mode(Con *con, bool automatic) {
    /* forbid the command to toggle floating on a CT_FLOATING_CON */
    if (con->type == CT_FLOATING_CON) {
        ELOG("Cannot toggle floating mode on con = %p because it is of type CT_FLOATING_CON.\n", con);
        return;
    }

    /* see if the client is already floating */
    if (con_is_floating(con)) {
        LOG("already floating, re-setting to tiling\n");

        floating_disable(con);
        return;
    }

    floating_enable(con, automatic);
}