#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xo_xof_flags_t ;
struct TYPE_10__ {int xo_style; void* xo_indent_by; } ;
typedef  TYPE_1__ xo_handle_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  XOF_CLEAR (TYPE_1__*,scalar_t__) ; 
 scalar_t__ XOF_COLOR_ALLOWED ; 
 scalar_t__ XOF_FLUSH ; 
 scalar_t__ XOF_FLUSH_LINE ; 
 scalar_t__ XOF_INFO ; 
 scalar_t__ XOF_KEYS ; 
 scalar_t__ XOF_LOG_GETTEXT ; 
 scalar_t__ XOF_NO_HUMANIZE ; 
 scalar_t__ XOF_PRETTY ; 
 int /*<<< orphan*/  XOF_SET (TYPE_1__*,scalar_t__) ; 
 scalar_t__ XOF_UNDERSCORES ; 
 scalar_t__ XOF_UNITS ; 
 scalar_t__ XOF_WARN ; 
 scalar_t__ XOF_XPATH ; 
 int XO_STYLE_ENCODER ; 
 int XO_STYLE_HTML ; 
 int XO_STYLE_JSON ; 
 int XO_STYLE_TEXT ; 
 int XO_STYLE_XML ; 
 char* alloca (int) ; 
 void* atoi (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* strchr (char*,char) ; 
 int strlen (char const*) ; 
 int strspn (char const*,char*) ; 
 TYPE_1__* xo_default (TYPE_1__*) ; 
 int xo_encoder_init (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  xo_failure (TYPE_1__*,char*) ; 
 scalar_t__ xo_name_to_flag (char*) ; 
 int xo_name_to_style (char*) ; 
 int /*<<< orphan*/  xo_set_color_map (TYPE_1__*,char*) ; 
 scalar_t__ xo_streq (char*,char*) ; 
 int /*<<< orphan*/  xo_warnx (char*,char*) ; 

int
xo_set_options (xo_handle_t *xop, const char *input)
{
    char *cp, *ep, *vp, *np, *bp;
    int style = -1, new_style, rc = 0;
    ssize_t len;
    xo_xof_flags_t new_flag;

    if (input == NULL)
	return 0;

    xop = xo_default(xop);

#ifdef LIBXO_COLOR_ON_BY_DEFAULT
    /* If the installer used --enable-color-on-by-default, then we allow it */
    XOF_SET(xop, XOF_COLOR_ALLOWED);
#endif /* LIBXO_COLOR_ON_BY_DEFAULT */

    /*
     * We support a simpler, old-school style of giving option
     * also, using a single character for each option.  It's
     * ideal for lazy people, such as myself.
     */
    if (*input == ':') {
	ssize_t sz;

	for (input++ ; *input; input++) {
	    switch (*input) {
	    case 'c':
		XOF_SET(xop, XOF_COLOR_ALLOWED);
		break;

	    case 'f':
		XOF_SET(xop, XOF_FLUSH);
		break;

	    case 'F':
		XOF_SET(xop, XOF_FLUSH_LINE);
		break;

	    case 'g':
		XOF_SET(xop, XOF_LOG_GETTEXT);
		break;

	    case 'H':
		xop->xo_style = XO_STYLE_HTML;
		break;

	    case 'I':
		XOF_SET(xop, XOF_INFO);
		break;

	    case 'i':
		sz = strspn(input + 1, "0123456789");
		if (sz > 0) {
		    xop->xo_indent_by = atoi(input + 1);
		    input += sz - 1;	/* Skip value */
		}
		break;

	    case 'J':
		xop->xo_style = XO_STYLE_JSON;
		break;

	    case 'k':
		XOF_SET(xop, XOF_KEYS);
		break;

	    case 'n':
		XOF_SET(xop, XOF_NO_HUMANIZE);
		break;

	    case 'P':
		XOF_SET(xop, XOF_PRETTY);
		break;

	    case 'T':
		xop->xo_style = XO_STYLE_TEXT;
		break;

	    case 'U':
		XOF_SET(xop, XOF_UNITS);
		break;

	    case 'u':
		XOF_SET(xop, XOF_UNDERSCORES);
		break;

	    case 'W':
		XOF_SET(xop, XOF_WARN);
		break;

	    case 'X':
		xop->xo_style = XO_STYLE_XML;
		break;

	    case 'x':
		XOF_SET(xop, XOF_XPATH);
		break;
	    }
	}
	return 0;
    }

    len = strlen(input) + 1;
    bp = alloca(len);
    memcpy(bp, input, len);

    for (cp = bp, ep = cp + len - 1; cp && cp < ep; cp = np) {
	np = strchr(cp, ',');
	if (np)
	    *np++ = '\0';

	vp = strchr(cp, '=');
	if (vp)
	    *vp++ = '\0';

	if (xo_streq("colors", cp)) {
	    xo_set_color_map(xop, vp);
	    continue;
	}

	/*
	 * For options, we don't allow "encoder" since we want to
	 * handle it explicitly below as "encoder=xxx".
	 */
	new_style = xo_name_to_style(cp);
	if (new_style >= 0 && new_style != XO_STYLE_ENCODER) {
	    if (style >= 0)
		xo_warnx("ignoring multiple styles: '%s'", cp);
	    else
		style = new_style;
	} else {
	    new_flag = xo_name_to_flag(cp);
	    if (new_flag != 0)
		XOF_SET(xop, new_flag);
	    else if (xo_streq(cp, "no-color"))
		XOF_CLEAR(xop, XOF_COLOR_ALLOWED);
	    else if (xo_streq(cp, "indent")) {
		if (vp)
		    xop->xo_indent_by = atoi(vp);
		else
		    xo_failure(xop, "missing value for indent option");
	    } else if (xo_streq(cp, "encoder")) {
		if (vp == NULL)
		    xo_failure(xop, "missing value for encoder option");
		else {
		    rc = xo_encoder_init(xop, vp);
		    if (rc)
			xo_warnx("error initializing encoder: %s", vp);
		}
		
	    } else {
		xo_warnx("unknown libxo option value: '%s'", cp);
		rc = -1;
	    }
	}
    }

    if (style > 0)
	xop->xo_style= style;

    return rc;
}