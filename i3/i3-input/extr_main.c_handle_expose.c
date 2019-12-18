#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_expose_event_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
typedef  int /*<<< orphan*/  i3String ;
typedef  int /*<<< orphan*/  color_t ;
struct TYPE_4__ {scalar_t__ height; scalar_t__ width; } ;

/* Variables and functions */
 int BORDER ; 
 scalar_t__ MAX_WIDTH ; 
 int PADDING ; 
 int /*<<< orphan*/  draw_util_hex_to_color (char*) ; 
 int /*<<< orphan*/  draw_util_rectangle (TYPE_1__*,int /*<<< orphan*/ ,int,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  draw_util_text (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 int /*<<< orphan*/  glyphs_ucs ; 
 int /*<<< orphan*/  i3string_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * i3string_from_ucs2 (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ input_position ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * prompt ; 
 int prompt_offset ; 
 TYPE_1__ surface ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_expose(void *data, xcb_connection_t *conn, xcb_expose_event_t *event) {
    printf("expose!\n");

    color_t border_color = draw_util_hex_to_color("#FF0000");
    color_t fg_color = draw_util_hex_to_color("#FFFFFF");
    color_t bg_color = draw_util_hex_to_color("#000000");

    int text_offset = BORDER + PADDING;

    /* draw border */
    draw_util_rectangle(&surface, border_color, 0, 0, surface.width, surface.height);

    /* draw background */
    draw_util_rectangle(&surface, bg_color, BORDER, BORDER, surface.width - 2 * BORDER, surface.height - 2 * BORDER);

    /* draw the prompt … */
    if (prompt != NULL) {
        draw_util_text(prompt, &surface, fg_color, bg_color, text_offset, text_offset, MAX_WIDTH - text_offset);
    }

    /* … and the text */
    if (input_position > 0) {
        i3String *input = i3string_from_ucs2(glyphs_ucs, input_position);
        draw_util_text(input, &surface, fg_color, bg_color, text_offset + prompt_offset, text_offset, MAX_WIDTH - text_offset);
        i3string_free(input);
    }

    xcb_flush(conn);

    return 1;
}