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
typedef  scalar_t__ shutdown_reason_t ;

/* Variables and functions */
 int /*<<< orphan*/  I3_IPC_EVENT_SHUTDOWN ; 
 scalar_t__ SHUTDOWN_REASON_EXIT ; 
 scalar_t__ SHUTDOWN_REASON_RESTART ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  get_buf ; 
 int /*<<< orphan*/  ipc_send_event (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  map_close ; 
 int /*<<< orphan*/  map_open ; 
 int /*<<< orphan*/  y (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ygenalloc () ; 
 int /*<<< orphan*/  ystr (char*) ; 

__attribute__((used)) static void ipc_send_shutdown_event(shutdown_reason_t reason) {
    yajl_gen gen = ygenalloc();
    y(map_open);

    ystr("change");

    if (reason == SHUTDOWN_REASON_RESTART) {
        ystr("restart");
    } else if (reason == SHUTDOWN_REASON_EXIT) {
        ystr("exit");
    }

    y(map_close);

    const unsigned char *payload;
    ylength length;

    y(get_buf, &payload, &length);
    ipc_send_event("shutdown", I3_IPC_EVENT_SHUTDOWN, (const char *)payload);

    y(free);
}