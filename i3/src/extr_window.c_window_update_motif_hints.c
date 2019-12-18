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
typedef  int /*<<< orphan*/  xcb_get_property_reply_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  i3Window ;
typedef  int /*<<< orphan*/  border_style_t ;

/* Variables and functions */
 int /*<<< orphan*/  BS_NONE ; 
 int /*<<< orphan*/  BS_NORMAL ; 
 int /*<<< orphan*/  BS_PIXEL ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *) ; 
 int MWM_DECOR_ALL ; 
 int MWM_DECOR_BORDER ; 
 int MWM_DECOR_TITLE ; 
 int MWM_HINTS_DECORATIONS ; 
 size_t MWM_HINTS_DECORATIONS_FIELD ; 
 size_t MWM_HINTS_FLAGS_FIELD ; 
 scalar_t__ xcb_get_property_value (int /*<<< orphan*/ *) ; 
 scalar_t__ xcb_get_property_value_length (int /*<<< orphan*/ *) ; 

void window_update_motif_hints(i3Window *win, xcb_get_property_reply_t *prop, border_style_t *motif_border_style) {
    /* This implementation simply mirrors Gnome's Metacity. Official
     * documentation of this hint is nowhere to be found.
     * For more information see:
     * https://people.gnome.org/~tthurman/docs/metacity/xprops_8h-source.html
     * https://stackoverflow.com/questions/13787553/detect-if-a-x11-window-has-decorations
     */
#define MWM_HINTS_FLAGS_FIELD 0
#define MWM_HINTS_DECORATIONS_FIELD 2

#define MWM_HINTS_DECORATIONS (1 << 1)
#define MWM_DECOR_ALL (1 << 0)
#define MWM_DECOR_BORDER (1 << 1)
#define MWM_DECOR_TITLE (1 << 3)

    if (motif_border_style != NULL)
        *motif_border_style = BS_NORMAL;

    if (prop == NULL || xcb_get_property_value_length(prop) == 0) {
        FREE(prop);
        return;
    }

    /* The property consists of an array of 5 uint32_t's. The first value is a
     * bit mask of what properties the hint will specify. We are only interested
     * in MWM_HINTS_DECORATIONS because it indicates that the third value of the
     * array tells us which decorations the window should have, each flag being
     * a particular decoration. Notice that X11 (Xlib) often mentions 32-bit
     * fields which in reality are implemented using unsigned long variables
     * (64-bits long on amd64 for example). On the other hand,
     * xcb_get_property_value() behaves strictly according to documentation,
     * i.e. returns 32-bit data fields. */
    uint32_t *motif_hints = (uint32_t *)xcb_get_property_value(prop);

    if (motif_border_style != NULL &&
        motif_hints[MWM_HINTS_FLAGS_FIELD] & MWM_HINTS_DECORATIONS) {
        if (motif_hints[MWM_HINTS_DECORATIONS_FIELD] & MWM_DECOR_ALL ||
            motif_hints[MWM_HINTS_DECORATIONS_FIELD] & MWM_DECOR_TITLE)
            *motif_border_style = BS_NORMAL;
        else if (motif_hints[MWM_HINTS_DECORATIONS_FIELD] & MWM_DECOR_BORDER)
            *motif_border_style = BS_PIXEL;
        else
            *motif_border_style = BS_NONE;
    }

    FREE(prop);

#undef MWM_HINTS_FLAGS_FIELD
#undef MWM_HINTS_DECORATIONS_FIELD
#undef MWM_HINTS_DECORATIONS
#undef MWM_DECOR_ALL
#undef MWM_DECOR_BORDER
#undef MWM_DECOR_TITLE
}