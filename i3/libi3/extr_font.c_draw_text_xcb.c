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
typedef  int /*<<< orphan*/  xcb_char2b_t ;
struct TYPE_6__ {TYPE_1__* info; } ;
struct TYPE_7__ {TYPE_2__ xcb; } ;
struct TYPE_8__ {TYPE_3__ specific; } ;
struct TYPE_5__ {int font_ascent; } ;

/* Variables and functions */
 int /*<<< orphan*/  conn ; 
 scalar_t__ predict_text_width_xcb (int /*<<< orphan*/  const*,int) ; 
 TYPE_4__* savedFont ; 
 int /*<<< orphan*/  xcb_image_text_16 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void draw_text_xcb(const xcb_char2b_t *text, size_t text_len, xcb_drawable_t drawable,
                          xcb_gcontext_t gc, int x, int y) {
    /* X11 coordinates for fonts start at the baseline */
    int pos_y = y + savedFont->specific.xcb.info->font_ascent;

    /* The X11 protocol limits text drawing to 255 chars, so we may need
     * multiple calls */
    int offset = 0;
    for (;;) {
        /* Calculate the size of this chunk */
        int chunk_size = (text_len > 255 ? 255 : text_len);
        const xcb_char2b_t *chunk = text + offset;

        /* Draw it */
        xcb_image_text_16(conn, chunk_size, drawable, gc, x, pos_y, chunk);

        /* Advance the offset and length of the text to draw */
        offset += chunk_size;
        text_len -= chunk_size;

        /* Check if we're done */
        if (text_len == 0)
            break;

        /* Advance pos_x based on the predicted text width */
        x += predict_text_width_xcb(chunk, chunk_size);
    }
}