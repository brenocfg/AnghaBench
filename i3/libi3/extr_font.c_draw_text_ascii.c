#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_gcontext_t ;
typedef  int /*<<< orphan*/  xcb_drawable_t ;
typedef  int /*<<< orphan*/  i3String ;
struct TYPE_6__ {TYPE_1__* info; } ;
struct TYPE_7__ {TYPE_2__ xcb; } ;
struct TYPE_8__ {int type; TYPE_3__ specific; } ;
struct TYPE_5__ {int /*<<< orphan*/  font_ascent; } ;

/* Variables and functions */
#define  FONT_TYPE_NONE 130 
#define  FONT_TYPE_PANGO 129 
#define  FONT_TYPE_XCB 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  draw_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  draw_text_pango (char const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  i3string_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * i3string_from_utf8 (char const*) ; 
 int /*<<< orphan*/  root_visual_type ; 
 TYPE_4__* savedFont ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  xcb_image_text_8 (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char const*) ; 

void draw_text_ascii(const char *text, xcb_drawable_t drawable,
                     xcb_gcontext_t gc, int x, int y, int max_width) {
    assert(savedFont != NULL);

    switch (savedFont->type) {
        case FONT_TYPE_NONE:
            /* Nothing to do */
            return;
        case FONT_TYPE_XCB: {
            size_t text_len = strlen(text);
            if (text_len > 255) {
                /* The text is too long to draw it directly to X */
                i3String *str = i3string_from_utf8(text);
                draw_text(str, drawable, gc, NULL, x, y, max_width);
                i3string_free(str);
            } else {
                /* X11 coordinates for fonts start at the baseline */
                int pos_y = y + savedFont->specific.xcb.info->font_ascent;

                xcb_image_text_8(conn, text_len, drawable, gc, x, pos_y, text);
            }
            break;
        }
        case FONT_TYPE_PANGO:
            /* Render the text using Pango */
            draw_text_pango(text, strlen(text),
                            drawable, root_visual_type, x, y, max_width, false);
            return;
    }
}