#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int xoc_effects; scalar_t__ xoc_col_fg; scalar_t__ xoc_col_bg; } ;
struct TYPE_5__ {int /*<<< orphan*/  xo_color_buf; TYPE_2__ xo_colors; } ;
typedef  TYPE_1__ xo_handle_t ;
typedef  TYPE_2__ xo_colors_t ;
typedef  int /*<<< orphan*/  xo_buffer_t ;

/* Variables and functions */
 scalar_t__ XO_COL_DEFAULT ; 
 int XO_EFF_INVERSE ; 
 int /*<<< orphan*/  xo_buf_append_str (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  xo_buf_reset (int /*<<< orphan*/ *) ; 
 char** xo_color_names ; 
 char const** xo_effect_names ; 

__attribute__((used)) static void
xo_colors_handle_html (xo_handle_t *xop, xo_colors_t *newp)
{
    xo_colors_t *oldp = &xop->xo_colors;

    /*
     * HTML colors are mostly trivial: fill in xo_color_buf with
     * a set of class tags representing the colors and effects.
     */

    /* If nothing changed, then do nothing */
    if (oldp->xoc_effects == newp->xoc_effects
	&& oldp->xoc_col_fg == newp->xoc_col_fg
	&& oldp->xoc_col_bg == newp->xoc_col_bg)
	return;

    unsigned i, bit;
    xo_buffer_t *xbp = &xop->xo_color_buf;

    xo_buf_reset(xbp);		/* We rebuild content after each change */

    for (i = 0, bit = 1; xo_effect_names[i]; i++, bit <<= 1) {
	if (!(newp->xoc_effects & bit))
	    continue;

	xo_buf_append_str(xbp, " effect-");
	xo_buf_append_str(xbp, xo_effect_names[i]);
    }

    const char *fg = NULL;
    const char *bg = NULL;

    if (newp->xoc_col_fg != XO_COL_DEFAULT)
	fg = xo_color_names[newp->xoc_col_fg];
    if (newp->xoc_col_bg != XO_COL_DEFAULT)
	bg = xo_color_names[newp->xoc_col_bg];

    if (newp->xoc_effects & XO_EFF_INVERSE) {
	const char *tmp = fg;
	fg = bg;
	bg = tmp;
	if (fg == NULL)
	    fg = "inverse";
	if (bg == NULL)
	    bg = "inverse";

    }

    if (fg) {
	xo_buf_append_str(xbp, " color-fg-");
	xo_buf_append_str(xbp, fg);
    }

    if (bg) {
	xo_buf_append_str(xbp, " color-bg-");
	xo_buf_append_str(xbp, bg);
    }
}