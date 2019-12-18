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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ ipc_client ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I3_IPC_REPLY_TYPE_COMMAND ; 
 int /*<<< orphan*/  ipc_push_pending (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_send_client_message (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void ipc_confirm_restart(ipc_client *client) {
    DLOG("ipc_confirm_restart(fd %d)\n", client->fd);
    static const char *reply = "[{\"success\":true}]";
    ipc_send_client_message(
        client, strlen(reply), I3_IPC_REPLY_TYPE_COMMAND,
        (const uint8_t *)reply);
    ipc_push_pending(client);
}