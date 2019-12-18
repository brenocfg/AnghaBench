#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ylength ;
typedef  int /*<<< orphan*/  yajl_gen ;
struct TYPE_7__ {TYPE_1__* window; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I3_IPC_EVENT_WINDOW ; 
 int /*<<< orphan*/  LC_NUMERIC ; 
 int /*<<< orphan*/  XCB_WINDOW_NONE ; 
 int /*<<< orphan*/  dump_node (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  get_buf ; 
 int /*<<< orphan*/  ipc_send_event (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  map_close ; 
 int /*<<< orphan*/  map_open ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  y (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ygenalloc () ; 
 int /*<<< orphan*/  ystr (char const*) ; 

void ipc_send_window_event(const char *property, Con *con) {
    DLOG("Issue IPC window %s event (con = %p, window = 0x%08x)\n",
         property, con, (con->window ? con->window->id : XCB_WINDOW_NONE));

    setlocale(LC_NUMERIC, "C");
    yajl_gen gen = ygenalloc();

    y(map_open);

    ystr("change");
    ystr(property);

    ystr("container");
    dump_node(gen, con, false);

    y(map_close);

    const unsigned char *payload;
    ylength length;
    y(get_buf, &payload, &length);

    ipc_send_event("window", I3_IPC_EVENT_WINDOW, (const char *)payload);
    y(free);
    setlocale(LC_NUMERIC, "");
}