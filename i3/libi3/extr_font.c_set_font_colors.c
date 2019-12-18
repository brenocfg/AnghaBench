#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_gcontext_t ;
typedef  int uint32_t ;
struct TYPE_9__ {int colorpixel; int /*<<< orphan*/  alpha; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
typedef  TYPE_3__ color_t ;
struct TYPE_7__ {int id; } ;
struct TYPE_8__ {TYPE_1__ xcb; } ;
struct TYPE_10__ {int type; TYPE_2__ specific; } ;

/* Variables and functions */
#define  FONT_TYPE_NONE 130 
#define  FONT_TYPE_PANGO 129 
#define  FONT_TYPE_XCB 128 
 int XCB_GC_BACKGROUND ; 
 int XCB_GC_FONT ; 
 int XCB_GC_FOREGROUND ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  pango_font_alpha ; 
 int /*<<< orphan*/  pango_font_blue ; 
 int /*<<< orphan*/  pango_font_green ; 
 int /*<<< orphan*/  pango_font_red ; 
 TYPE_6__* savedFont ; 
 int /*<<< orphan*/  xcb_change_gc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

void set_font_colors(xcb_gcontext_t gc, color_t foreground, color_t background) {
    assert(savedFont != NULL);

    switch (savedFont->type) {
        case FONT_TYPE_NONE:
            /* Nothing to do */
            break;
        case FONT_TYPE_XCB: {
            /* Change the font and colors in the GC */
            uint32_t mask = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND | XCB_GC_FONT;
            uint32_t values[] = {foreground.colorpixel, background.colorpixel, savedFont->specific.xcb.id};
            xcb_change_gc(conn, gc, mask, values);
            break;
        }
        case FONT_TYPE_PANGO:
            /* Save the foreground font */
            pango_font_red = foreground.red;
            pango_font_green = foreground.green;
            pango_font_blue = foreground.blue;
            pango_font_alpha = foreground.alpha;
            break;
    }
}