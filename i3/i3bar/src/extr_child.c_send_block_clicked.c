#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  click_events; } ;

/* Variables and functions */
 int XCB_MOD_MASK_1 ; 
 int XCB_MOD_MASK_2 ; 
 int XCB_MOD_MASK_3 ; 
 int XCB_MOD_MASK_4 ; 
 int XCB_MOD_MASK_5 ; 
 int XCB_MOD_MASK_CONTROL ; 
 int XCB_MOD_MASK_SHIFT ; 
 TYPE_1__ child ; 
 int /*<<< orphan*/  child_click_events_initialize () ; 
 int /*<<< orphan*/  child_write_output () ; 
 int /*<<< orphan*/  gen ; 
 int /*<<< orphan*/  yajl_gen_array_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yajl_gen_array_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yajl_gen_integer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  yajl_gen_map_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yajl_gen_map_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ystr (char const*) ; 

void send_block_clicked(int button, const char *name, const char *instance, int x, int y, int x_rel, int y_rel, int width, int height, int mods) {
    if (!child.click_events) {
        return;
    }

    child_click_events_initialize();

    yajl_gen_map_open(gen);

    if (name) {
        ystr("name");
        ystr(name);
    }

    if (instance) {
        ystr("instance");
        ystr(instance);
    }

    ystr("button");
    yajl_gen_integer(gen, button);

    ystr("modifiers");
    yajl_gen_array_open(gen);
    if (mods & XCB_MOD_MASK_SHIFT)
        ystr("Shift");
    if (mods & XCB_MOD_MASK_CONTROL)
        ystr("Control");
    if (mods & XCB_MOD_MASK_1)
        ystr("Mod1");
    if (mods & XCB_MOD_MASK_2)
        ystr("Mod2");
    if (mods & XCB_MOD_MASK_3)
        ystr("Mod3");
    if (mods & XCB_MOD_MASK_4)
        ystr("Mod4");
    if (mods & XCB_MOD_MASK_5)
        ystr("Mod5");
    yajl_gen_array_close(gen);

    ystr("x");
    yajl_gen_integer(gen, x);

    ystr("y");
    yajl_gen_integer(gen, y);

    ystr("relative_x");
    yajl_gen_integer(gen, x_rel);

    ystr("relative_y");
    yajl_gen_integer(gen, y_rel);

    ystr("width");
    yajl_gen_integer(gen, width);

    ystr("height");
    yajl_gen_integer(gen, height);

    yajl_gen_map_close(gen);
    child_write_output();
}