#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_3__ {char* bar_fg; } ;
struct TYPE_4__ {TYPE_1__ colors; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,char const*) ; 
 int /*<<< orphan*/  XCB_ATOM_CARDINAL ; 
 int /*<<< orphan*/  XCB_PROP_MODE_REPLACE ; 
 size_t _NET_SYSTEM_TRAY_COLORS ; 
 int /*<<< orphan*/ * atoms ; 
 TYPE_2__ config ; 
 int /*<<< orphan*/  selwin ; 
 int strtol (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xcb_change_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int const*) ; 
 int /*<<< orphan*/  xcb_connection ; 

void init_tray_colors(void) {
    /* Convert colors.bar_fg (#rrggbb) to 16-bit RGB */
    const char *bar_fg = (config.colors.bar_fg ? config.colors.bar_fg : "#FFFFFF");

    DLOG("Setting bar_fg = %s as _NET_SYSTEM_TRAY_COLORS\n", bar_fg);

    char strgroups[3][3] = {{bar_fg[1], bar_fg[2], '\0'},
                            {bar_fg[3], bar_fg[4], '\0'},
                            {bar_fg[5], bar_fg[6], '\0'}};
    const uint8_t r = strtol(strgroups[0], NULL, 16);
    const uint8_t g = strtol(strgroups[1], NULL, 16);
    const uint8_t b = strtol(strgroups[2], NULL, 16);

    const uint16_t r16 = ((uint16_t)r << 8) | r;
    const uint16_t g16 = ((uint16_t)g << 8) | g;
    const uint16_t b16 = ((uint16_t)b << 8) | b;

    const uint32_t tray_colors[12] = {
        r16, g16, b16, /* foreground color */
        r16, g16, b16, /* error color */
        r16, g16, b16, /* warning color */
        r16, g16, b16, /* success color */
    };

    xcb_change_property(xcb_connection,
                        XCB_PROP_MODE_REPLACE,
                        selwin,
                        atoms[_NET_SYSTEM_TRAY_COLORS],
                        XCB_ATOM_CARDINAL,
                        32,
                        12,
                        tray_colors);
}