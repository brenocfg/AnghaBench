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
struct TYPE_6__ {int xoc_effects; scalar_t__ xoc_col_fg; scalar_t__ xoc_col_bg; } ;
struct TYPE_5__ {int /*<<< orphan*/  xo_data; TYPE_2__ xo_colors; } ;
typedef  TYPE_1__ xo_handle_t ;
typedef  TYPE_2__ xo_colors_t ;
typedef  scalar_t__ xo_color_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BUFSIZ ; 
 scalar_t__ XO_COL_DEFAULT ; 
 unsigned int XO_EFF_RESET ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  xo_buf_append (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__* xo_effect_names ; 
 char** xo_effect_on_codes ; 

__attribute__((used)) static void
xo_colors_handle_text (xo_handle_t *xop, xo_colors_t *newp)
{
    char buf[BUFSIZ];
    char *cp = buf, *ep = buf + sizeof(buf);
    unsigned i, bit;
    xo_colors_t *oldp = &xop->xo_colors;
    const char *code = NULL;

    /*
     * Start the buffer with an escape.  We don't want to add the '['
     * now, since we let xo_effect_text_add unconditionally add the ';'.
     * We'll replace the first ';' with a '[' when we're done.
     */
    *cp++ = 0x1b;		/* Escape */

    /*
     * Terminals were designed back in the age before "certainty" was
     * invented, when standards were more what you'd call "guidelines"
     * than actual rules.  Anyway we can't depend on them to operate
     * correctly.  So when display attributes are changed, we punt,
     * reseting them all and turning back on the ones we want to keep.
     * Longer, but should be completely reliable.  Savvy?
     */
    if (oldp->xoc_effects != (newp->xoc_effects & oldp->xoc_effects)) {
	newp->xoc_effects |= XO_EFF_RESET;
	oldp->xoc_effects = 0;
    }

    for (i = 0, bit = 1; xo_effect_names[i]; i++, bit <<= 1) {
	if ((newp->xoc_effects & bit) == (oldp->xoc_effects & bit))
	    continue;

	code = xo_effect_on_codes[i];

	cp += snprintf(cp, ep - cp, ";%s", code);
	if (cp >= ep)
	    return;		/* Should not occur */

	if (bit == XO_EFF_RESET) {
	    /* Mark up the old value so we can detect current values as new */
	    oldp->xoc_effects = 0;
	    oldp->xoc_col_fg = oldp->xoc_col_bg = XO_COL_DEFAULT;
	}
    }

    xo_color_t fg = newp->xoc_col_fg;
    if (fg != oldp->xoc_col_fg) {
	cp += snprintf(cp, ep - cp, ";3%u",
		       (fg != XO_COL_DEFAULT) ? fg - 1 : 9);
    }

    xo_color_t bg = newp->xoc_col_bg;
    if (bg != oldp->xoc_col_bg) {
	cp += snprintf(cp, ep - cp, ";4%u",
		       (bg != XO_COL_DEFAULT) ? bg - 1 : 9);
    }

    if (cp - buf != 1 && cp < ep - 3) {
	buf[1] = '[';		/* Overwrite leading ';' */
	*cp++ = 'm';
	*cp = '\0';
	xo_buf_append(&xop->xo_data, buf, cp - buf);
    }
}