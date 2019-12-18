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

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*) ; 
 int /*<<< orphan*/  I3_IPC_MESSAGE_TYPE_GET_WORKSPACES ; 
 int /*<<< orphan*/  i3_send_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void got_workspace_event(char *event) {
    DLOG("Got workspace event!\n");
    i3_send_msg(I3_IPC_MESSAGE_TYPE_GET_WORKSPACES, NULL);
}