#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ylength ;
typedef  int /*<<< orphan*/  yajl_gen ;
typedef  int /*<<< orphan*/  Con ;

/* Variables and functions */
 int /*<<< orphan*/  I3_IPC_EVENT_WORKSPACE ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  get_buf ; 
 int /*<<< orphan*/  ipc_marshal_workspace_event (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_send_event (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  y (int /*<<< orphan*/ ,...) ; 

void ipc_send_workspace_event(const char *change, Con *current, Con *old) {
    yajl_gen gen = ipc_marshal_workspace_event(change, current, old);

    const unsigned char *payload;
    ylength length;
    y(get_buf, &payload, &length);

    ipc_send_event("workspace", I3_IPC_EVENT_WORKSPACE, (const char *)payload);

    y(free);
}