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
typedef  int /*<<< orphan*/  color_t ;

/* Variables and functions */
 scalar_t__ MOD_Mod4 ; 
 scalar_t__ STEP_GENERATE ; 
 scalar_t__ STEP_WELCOME ; 
 int /*<<< orphan*/  bold_font ; 
 int /*<<< orphan*/  config_path ; 
 int /*<<< orphan*/  conn ; 
 scalar_t__ current_step ; 
 int /*<<< orphan*/  draw_util_clear_surface (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  draw_util_hex_to_color (char*) ; 
 int /*<<< orphan*/  font ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ modifier ; 
 int /*<<< orphan*/  sasprintf (char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_font (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  surface ; 
 int /*<<< orphan*/  txt (int,int,char*,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_expose(void) {
    const color_t black = draw_util_hex_to_color("#000000");
    const color_t white = draw_util_hex_to_color("#FFFFFF");
    const color_t green = draw_util_hex_to_color("#00FF00");
    const color_t red = draw_util_hex_to_color("#FF0000");

    /* draw background */
    draw_util_clear_surface(&surface, black);

    set_font(&font);

    if (current_step == STEP_WELCOME) {
        txt(2, 2, "You have not configured i3 yet.", white, black);
        txt(2, 3, "Do you want me to generate a config at", white, black);

        char *msg;
        sasprintf(&msg, "%s?", config_path);
        txt(2, 4, msg, white, black);
        free(msg);

        txt(13, 6, "Yes, generate the config", white, black);
        txt(13, 8, "No, I will use the defaults", white, black);

        txt(4, 6, "<Enter>", green, black);

        txt(5, 8, "<ESC>", red, black);
    }

    if (current_step == STEP_GENERATE) {
        txt(2, 2, "Please choose either:", white, black);
        txt(13, 4, "Win as default modifier", white, black);
        txt(13, 5, "Alt as default modifier", white, black);
        txt(2, 7, "Afterwards, press", white, black);
        txt(13, 9, "to write the config", white, black);
        txt(13, 10, "to abort", white, black);

        /* the not-selected modifier */
        if (modifier == MOD_Mod4)
            txt(5, 5, "<Alt>", white, black);
        else
            txt(5, 4, "<Win>", white, black);

        /* the selected modifier */
        set_font(&bold_font);
        if (modifier == MOD_Mod4)
            txt(2, 4, "-> <Win>", white, black);
        else
            txt(2, 5, "-> <Alt>", white, black);

        set_font(&font);
        txt(4, 9, "<Enter>", green, black);

        txt(5, 10, "<ESC>", red, black);
    }

    xcb_flush(conn);

    return 1;
}