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
struct TYPE_4__ {int /*<<< orphan*/  keycode; int /*<<< orphan*/  symbol; } ;
typedef  TYPE_1__ Binding ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I3_IPC_EVENT_BINDING ; 
 int /*<<< orphan*/  LC_NUMERIC ; 
 int /*<<< orphan*/  dump_binding (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  get_buf ; 
 int /*<<< orphan*/  ipc_send_event (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  map_close ; 
 int /*<<< orphan*/  map_open ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  y (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ygenalloc () ; 
 int /*<<< orphan*/  ystr (char const*) ; 

void ipc_send_binding_event(const char *event_type, Binding *bind) {
    DLOG("Issue IPC binding %s event (sym = %s, code = %d)\n", event_type, bind->symbol, bind->keycode);

    setlocale(LC_NUMERIC, "C");

    yajl_gen gen = ygenalloc();

    y(map_open);

    ystr("change");
    ystr(event_type);

    ystr("binding");
    dump_binding(gen, bind);

    y(map_close);

    const unsigned char *payload;
    ylength length;
    y(get_buf, &payload, &length);

    ipc_send_event("binding", I3_IPC_EVENT_BINDING, (const char *)payload);

    y(free);
    setlocale(LC_NUMERIC, "");
}