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
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_1__ frame; } ;
typedef  TYPE_2__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  _x_con_kill (TYPE_2__*) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  xcb_destroy_window (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void x_con_kill(Con *con) {
    _x_con_kill(con);
    xcb_destroy_window(conn, con->frame.id);
}