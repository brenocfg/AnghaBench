#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ylength ;
typedef  int /*<<< orphan*/  yajl_gen ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ Barconfig ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I3_IPC_EVENT_BARCONFIG_UPDATE ; 
 int /*<<< orphan*/  LC_NUMERIC ; 
 int /*<<< orphan*/  dump_bar_config (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  get_buf ; 
 int /*<<< orphan*/  ipc_send_event (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  y (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ygenalloc () ; 

void ipc_send_barconfig_update_event(Barconfig *barconfig) {
    DLOG("Issue barconfig_update event for id = %s\n", barconfig->id);
    setlocale(LC_NUMERIC, "C");
    yajl_gen gen = ygenalloc();

    dump_bar_config(gen, barconfig);

    const unsigned char *payload;
    ylength length;
    y(get_buf, &payload, &length);

    ipc_send_event("barconfig_update", I3_IPC_EVENT_BARCONFIG_UPDATE, (const char *)payload);
    y(free);
    setlocale(LC_NUMERIC, "");
}