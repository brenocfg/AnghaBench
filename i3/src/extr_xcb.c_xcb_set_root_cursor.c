#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_cursor_t ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_1__ xcb; } ;
struct TYPE_7__ {TYPE_2__ specific; } ;
typedef  TYPE_3__ i3Font ;

/* Variables and functions */
 int /*<<< orphan*/  XCB_CW_CURSOR ; 
 int /*<<< orphan*/  conn ; 
 TYPE_3__ load_font (char*,int) ; 
 int /*<<< orphan*/  root ; 
 int /*<<< orphan*/  xcb_change_window_attributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_create_glyph_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_free_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_generate_id (int /*<<< orphan*/ ) ; 
 int xcursor_get_xcb_cursor (int) ; 

void xcb_set_root_cursor(int cursor) {
    xcb_cursor_t cursor_id = xcb_generate_id(conn);
    i3Font cursor_font = load_font("cursor", false);
    int xcb_cursor = xcursor_get_xcb_cursor(cursor);
    xcb_create_glyph_cursor(conn, cursor_id, cursor_font.specific.xcb.id,
                            cursor_font.specific.xcb.id, xcb_cursor, xcb_cursor + 1, 0, 0, 0,
                            65535, 65535, 65535);
    xcb_change_window_attributes(conn, root, XCB_CW_CURSOR, &cursor_id);
    xcb_free_cursor(conn, cursor_id);
    xcb_flush(conn);
}