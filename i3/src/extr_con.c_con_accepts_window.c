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
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/ * window; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 scalar_t__ CT_WORKSPACE ; 
 int /*<<< orphan*/  DLOG (char*,TYPE_1__*) ; 
 scalar_t__ con_is_split (TYPE_1__*) ; 

bool con_accepts_window(Con *con) {
    /* 1: workspaces never accept direct windows */
    if (con->type == CT_WORKSPACE)
        return false;

    if (con_is_split(con)) {
        DLOG("container %p does not accept windows, it is a split container.\n", con);
        return false;
    }

    /* TODO: if this is a swallowing container, we need to check its max_clients */
    return (con->window == NULL);
}