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
typedef  int /*<<< orphan*/  i3String ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  FONT_TYPE_NONE 130 
#define  FONT_TYPE_PANGO 129 
#define  FONT_TYPE_XCB 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  i3string_as_ucs2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i3string_as_utf8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i3string_get_num_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i3string_get_num_glyphs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i3string_is_markup (int /*<<< orphan*/ *) ; 
 int predict_text_width_pango (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int predict_text_width_xcb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* savedFont ; 

int predict_text_width(i3String *text) {
    assert(savedFont != NULL);

    switch (savedFont->type) {
        case FONT_TYPE_NONE:
            /* Nothing to do */
            return 0;
        case FONT_TYPE_XCB:
            return predict_text_width_xcb(i3string_as_ucs2(text), i3string_get_num_glyphs(text));
        case FONT_TYPE_PANGO:
            /* Calculate extents using Pango */
            return predict_text_width_pango(i3string_as_utf8(text), i3string_get_num_bytes(text),
                                            i3string_is_markup(text));
    }
    assert(false);
}