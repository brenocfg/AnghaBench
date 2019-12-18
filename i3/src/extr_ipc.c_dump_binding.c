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
typedef  int /*<<< orphan*/  yajl_gen ;
struct TYPE_4__ {scalar_t__ input_type; char* symbol; char* command; int /*<<< orphan*/  keycode; } ;
typedef  TYPE_1__ Binding ;

/* Variables and functions */
 scalar_t__ B_KEYBOARD ; 
 int /*<<< orphan*/  dump_event_state_mask (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  integer ; 
 int /*<<< orphan*/  map_close ; 
 int /*<<< orphan*/  map_open ; 
 int /*<<< orphan*/  null ; 
 int /*<<< orphan*/  y (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ystr (char const*) ; 

__attribute__((used)) static void dump_binding(yajl_gen gen, Binding *bind) {
    y(map_open);
    ystr("input_code");
    y(integer, bind->keycode);

    ystr("input_type");
    ystr((const char *)(bind->input_type == B_KEYBOARD ? "keyboard" : "mouse"));

    ystr("symbol");
    if (bind->symbol == NULL)
        y(null);
    else
        ystr(bind->symbol);

    ystr("command");
    ystr(bind->command);

    // This key is only provided for compatibility, new programs should use
    // event_state_mask instead.
    ystr("mods");
    dump_event_state_mask(gen, bind);

    ystr("event_state_mask");
    dump_event_state_mask(gen, bind);

    y(map_close);
}