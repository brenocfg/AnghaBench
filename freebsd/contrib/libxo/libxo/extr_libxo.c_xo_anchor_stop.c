#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ xb_curp; scalar_t__ xb_bufp; } ;
struct TYPE_10__ {scalar_t__ xo_anchor_min_width; scalar_t__ xo_anchor_offset; scalar_t__ xo_anchor_columns; TYPE_2__ xo_data; } ;
typedef  TYPE_1__ xo_handle_t ;
typedef  int /*<<< orphan*/  xo_field_info_t ;
typedef  TYPE_2__ xo_buffer_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  XOIF_ANCHOR ; 
 int /*<<< orphan*/  XOIF_CLEAR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOIF_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOIF_UNITS_PENDING ; 
 scalar_t__ XO_MAX_ANCHOR_WIDTH ; 
 char* alloca (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memmove (scalar_t__,char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (char*,char,scalar_t__) ; 
 int /*<<< orphan*/  xo_anchor_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  xo_failure (TYPE_1__*,char*,...) ; 
 scalar_t__ xo_find_width (TYPE_1__*,int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 int /*<<< orphan*/  xo_format_content (TYPE_1__*,char*,int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xo_anchor_stop (xo_handle_t *xop, xo_field_info_t *xfip,
		 const char *value, ssize_t vlen)
{
    if (!XOIF_ISSET(xop, XOIF_ANCHOR)) {
	xo_failure(xop, "no start anchor");
	return;
    }

    XOIF_CLEAR(xop, XOIF_UNITS_PENDING);

    ssize_t width = xo_find_width(xop, xfip, value, vlen);
    if (width == 0)
	width = xop->xo_anchor_min_width;

    if (width == 0)		/* No width given; nothing to do */
	goto done;

    xo_buffer_t *xbp = &xop->xo_data;
    ssize_t start = xop->xo_anchor_offset;
    ssize_t stop = xbp->xb_curp - xbp->xb_bufp;
    ssize_t abswidth = (width > 0) ? width : -width;
    ssize_t blen = abswidth - xop->xo_anchor_columns;

    if (blen <= 0)		/* Already over width */
	goto done;

    if (abswidth > XO_MAX_ANCHOR_WIDTH) {
	xo_failure(xop, "width over %u are not supported",
		   XO_MAX_ANCHOR_WIDTH);
	goto done;
    }

    /* Make a suitable padding field and emit it */
    char *buf = alloca(blen);
    memset(buf, ' ', blen);
    xo_format_content(xop, "padding", NULL, buf, blen, NULL, 0, 0);

    if (width < 0)		/* Already left justified */
	goto done;

    ssize_t now = xbp->xb_curp - xbp->xb_bufp;
    ssize_t delta = now - stop;
    if (delta <= 0)		/* Strange; no output to move */
	goto done;

    /*
     * Now we're in it alright.  We've need to insert the padding data
     * we just created (which might be an HTML <div> or text) before
     * the formatted data.  We make a local copy, move it and then
     * insert our copy.  We know there's room in the buffer, since
     * we're just moving this around.
     */
    if (delta > blen)
	buf = alloca(delta);	/* Expand buffer if needed */

    memcpy(buf, xbp->xb_bufp + stop, delta);
    memmove(xbp->xb_bufp + start + delta, xbp->xb_bufp + start, stop - start);
    memmove(xbp->xb_bufp + start, buf, delta);

 done:
    xo_anchor_clear(xop);
}