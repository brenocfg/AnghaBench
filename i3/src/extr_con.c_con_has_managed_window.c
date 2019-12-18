#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* window; } ;
struct TYPE_5__ {scalar_t__ id; } ;
typedef  TYPE_2__ Con ;

/* Variables and functions */
 scalar_t__ XCB_WINDOW_NONE ; 
 int /*<<< orphan*/ * con_get_workspace (TYPE_2__*) ; 

bool con_has_managed_window(Con *con) {
    return (con != NULL && con->window != NULL && con->window->id != XCB_WINDOW_NONE && con_get_workspace(con) != NULL);
}