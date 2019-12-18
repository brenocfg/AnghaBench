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
typedef  int /*<<< orphan*/  xcb_visualtype_t ;
typedef  int /*<<< orphan*/  xcb_gcontext_t ;
typedef  int /*<<< orphan*/  xcb_drawable_t ;
typedef  int /*<<< orphan*/  i3String ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  FONT_TYPE_NONE 130 
#define  FONT_TYPE_PANGO 129 
#define  FONT_TYPE_XCB 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_text_pango (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_text_xcb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  i3string_as_ucs2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i3string_as_utf8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i3string_get_num_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i3string_get_num_glyphs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i3string_is_markup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * root_visual_type ; 
 TYPE_1__* savedFont ; 

void draw_text(i3String *text, xcb_drawable_t drawable, xcb_gcontext_t gc,
               xcb_visualtype_t *visual, int x, int y, int max_width) {
    assert(savedFont != NULL);
    if (visual == NULL) {
        visual = root_visual_type;
    }

    switch (savedFont->type) {
        case FONT_TYPE_NONE:
            /* Nothing to do */
            return;
        case FONT_TYPE_XCB:
            draw_text_xcb(i3string_as_ucs2(text), i3string_get_num_glyphs(text),
                          drawable, gc, x, y);
            break;
        case FONT_TYPE_PANGO:
            /* Render the text using Pango */
            draw_text_pango(i3string_as_utf8(text), i3string_get_num_bytes(text),
                            drawable, visual, x, y, max_width, i3string_is_markup(text));
            return;
    }
}