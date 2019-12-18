#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xo_xff_flags_t ;
struct TYPE_21__ {char* xb_curp; char* xb_bufp; int xb_size; } ;
struct TYPE_19__ {int xo_columns; int xo_anchor_columns; TYPE_3__ xo_data; int /*<<< orphan*/  xo_indent_by; } ;
typedef  TYPE_1__ xo_handle_t ;
struct TYPE_20__ {char* xfi_format; int xfi_flen; int /*<<< orphan*/  xfi_flags; } ;
typedef  TYPE_2__ xo_field_info_t ;
typedef  TYPE_3__ xo_buffer_t ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  div_open ;
typedef  int /*<<< orphan*/  div_middle ;
typedef  int /*<<< orphan*/  div_close ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XOF_COLUMNS ; 
 scalar_t__ XOF_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOF_PRETTY ; 
 int /*<<< orphan*/  XOIF_ANCHOR ; 
 scalar_t__ XOIF_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
#define  XO_STYLE_ENCODER 131 
 int XO_STYLE_HTML ; 
#define  XO_STYLE_JSON 130 
#define  XO_STYLE_SDPARAMS 129 
#define  XO_STYLE_XML 128 
 char* alloca (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  xo_buf_append (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  xo_buf_has_room (TYPE_3__*,int) ; 
 int /*<<< orphan*/  xo_buf_indent (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_color_append_html (TYPE_1__*) ; 
 int /*<<< orphan*/  xo_data_append (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  xo_data_append_content (TYPE_1__*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_do_format_field (TYPE_1__*,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 
 int xo_escape_xml (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_line_ensure_open (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_simple_field (TYPE_1__*,int /*<<< orphan*/ ,char const*,int,char const*,int,int /*<<< orphan*/ ) ; 
 int xo_style (TYPE_1__*) ; 

__attribute__((used)) static void
xo_format_title (xo_handle_t *xop, xo_field_info_t *xfip,
		 const char *value, ssize_t vlen)
{
    const char *fmt = xfip->xfi_format;
    ssize_t flen = xfip->xfi_flen;
    xo_xff_flags_t flags = xfip->xfi_flags;

    static char div_open[] = "<div class=\"title";
    static char div_middle[] = "\">";
    static char div_close[] = "</div>";

    if (flen == 0) {
	fmt = "%s";
	flen = 2;
    }

    switch (xo_style(xop)) {
    case XO_STYLE_XML:
    case XO_STYLE_JSON:
    case XO_STYLE_SDPARAMS:
    case XO_STYLE_ENCODER:
	/*
	 * Even though we don't care about text, we need to do
	 * enough parsing work to skip over the right bits of xo_vap.
	 */
	xo_simple_field(xop, TRUE, value, vlen, fmt, flen, flags);
	return;
    }

    xo_buffer_t *xbp = &xop->xo_data;
    ssize_t start = xbp->xb_curp - xbp->xb_bufp;
    ssize_t left = xbp->xb_size - start;
    ssize_t rc;

    if (xo_style(xop) == XO_STYLE_HTML) {
	xo_line_ensure_open(xop, 0);
	if (XOF_ISSET(xop, XOF_PRETTY))
	    xo_buf_indent(xop, xop->xo_indent_by);
	xo_buf_append(&xop->xo_data, div_open, sizeof(div_open) - 1);
	xo_color_append_html(xop);
	xo_buf_append(&xop->xo_data, div_middle, sizeof(div_middle) - 1);
    }

    start = xbp->xb_curp - xbp->xb_bufp; /* Reset start */
    if (vlen) {
	char *newfmt = alloca(flen + 1);
	memcpy(newfmt, fmt, flen);
	newfmt[flen] = '\0';

	/* If len is non-zero, the format string apply to the name */
	char *newstr = alloca(vlen + 1);
	memcpy(newstr, value, vlen);
	newstr[vlen] = '\0';

	if (newstr[vlen - 1] == 's') {
	    char *bp;

	    rc = snprintf(NULL, 0, newfmt, newstr);
	    if (rc > 0) {
		/*
		 * We have to do this the hard way, since we might need
		 * the columns.
		 */
		bp = alloca(rc + 1);
		rc = snprintf(bp, rc + 1, newfmt, newstr);

		xo_data_append_content(xop, bp, rc, flags);
	    }
	    goto move_along;

	} else {
	    rc = snprintf(xbp->xb_curp, left, newfmt, newstr);
	    if (rc >= left) {
		if (!xo_buf_has_room(xbp, rc))
		    return;
		left = xbp->xb_size - (xbp->xb_curp - xbp->xb_bufp);
		rc = snprintf(xbp->xb_curp, left, newfmt, newstr);
	    }

	    if (rc > 0) {
		if (XOF_ISSET(xop, XOF_COLUMNS))
		    xop->xo_columns += rc;
		if (XOIF_ISSET(xop, XOIF_ANCHOR))
		    xop->xo_anchor_columns += rc;
	    }
	}

    } else {
	xo_do_format_field(xop, NULL, fmt, flen, flags);

	/* xo_do_format_field moved curp, so we need to reset it */
	rc = xbp->xb_curp - (xbp->xb_bufp + start);
	xbp->xb_curp = xbp->xb_bufp + start;
    }

    /* If we're styling HTML, then we need to escape it */
    if (xo_style(xop) == XO_STYLE_HTML) {
	rc = xo_escape_xml(xbp, rc, 0);
    }

    if (rc > 0)
	xbp->xb_curp += rc;

 move_along:
    if (xo_style(xop) == XO_STYLE_HTML) {
	xo_data_append(xop, div_close, sizeof(div_close) - 1);
	if (XOF_ISSET(xop, XOF_PRETTY))
	    xo_data_append(xop, "\n", 1);
    }
}