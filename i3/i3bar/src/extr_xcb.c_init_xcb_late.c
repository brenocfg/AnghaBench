#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ bar_height; scalar_t__ hide_on_modifier; scalar_t__ separator_symbol; int /*<<< orphan*/  tray_padding; } ;
struct TYPE_5__ {scalar_t__ height; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,scalar_t__) ; 
 scalar_t__ M_HIDE ; 
 scalar_t__ bar_height ; 
 TYPE_4__ config ; 
 TYPE_1__ font ; 
 scalar_t__ icon_size ; 
 TYPE_1__ load_font (char*,int) ; 
 int logical_px (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  predict_text_width (scalar_t__) ; 
 int /*<<< orphan*/  register_xkb_keyevents () ; 
 int /*<<< orphan*/  separator_symbol_width ; 
 int /*<<< orphan*/  set_font (TYPE_1__*) ; 
 int /*<<< orphan*/  ws_voff_px ; 
 int /*<<< orphan*/  xcb_connection ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ ) ; 

void init_xcb_late(char *fontname) {
    if (fontname == NULL)
        fontname = "-misc-fixed-medium-r-normal--13-120-75-75-C-70-iso10646-1";

    /* Load the font */
    font = load_font(fontname, true);
    set_font(&font);
    DLOG("Calculated font-height: %d\n", font.height);

    /*
     * If the bar height was explicitly set, use it. Otherwise, calculate it
     * based on the font size.
     */
    if (config.bar_height <= 0)
        bar_height = font.height + 2 * logical_px(ws_voff_px);
    else
        bar_height = config.bar_height;
    icon_size = bar_height - 2 * logical_px(config.tray_padding);

    if (config.separator_symbol)
        separator_symbol_width = predict_text_width(config.separator_symbol);

    xcb_flush(xcb_connection);

    if (config.hide_on_modifier == M_HIDE)
        register_xkb_keyevents();
}