#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int num_of_uniforms; TYPE_1__* uniforms; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  location; } ;
typedef  TYPE_2__ Program ;

/* Variables and functions */
 int BORDERS_PROGRAM ; 
 size_t BORDER_active_border_color ; 
 size_t BORDER_background_opacity ; 
 size_t BORDER_bell_border_color ; 
 size_t BORDER_default_bg ; 
 size_t BORDER_inactive_border_color ; 
 size_t BORDER_viewport ; 
 int NUM_BORDER_UNIFORMS ; 
 int /*<<< orphan*/ * border_uniform_locations ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 TYPE_2__* programs ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
init_borders_program() {
    Program *p = programs + BORDERS_PROGRAM;
    int left = NUM_BORDER_UNIFORMS;
    for (int i = 0; i < p->num_of_uniforms; i++, left--) {
#define SET_LOC(which) (strcmp(p->uniforms[i].name, #which) == 0) border_uniform_locations[BORDER_##which] = p->uniforms[i].location
        if SET_LOC(viewport);
        else if SET_LOC(background_opacity);
        else if SET_LOC(default_bg);
        else if SET_LOC(active_border_color);
        else if SET_LOC(inactive_border_color);
        else if SET_LOC(bell_border_color);
        else { fatal("Unknown uniform in borders program: %s", p->uniforms[i].name); return; }
    }
    if (left) { fatal("Left over uniforms in borders program"); return; }
#undef SET_LOC
}