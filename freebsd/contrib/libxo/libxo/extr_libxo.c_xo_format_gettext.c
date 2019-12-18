#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int xo_xff_flags_t ;
struct TYPE_12__ {char* xb_curp; char* xb_bufp; } ;
struct TYPE_11__ {TYPE_2__ xo_data; } ;
typedef  TYPE_1__ xo_handle_t ;
typedef  TYPE_2__ xo_buffer_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int XFF_GT_FIELD ; 
 int XFF_GT_PLURAL ; 
 int XF_ENC_UTF8 ; 
 char* alloca (int) ; 
 char* memchr (char*,int,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 
 int xo_buf_find_last_number (TYPE_2__*,int) ; 
 int /*<<< orphan*/  xo_buf_has_room (TYPE_2__*,int) ; 
 int xo_count_utf8_cols (char*,int) ; 
 char* xo_dgettext (TYPE_1__*,char*) ; 
 char* xo_dngettext (TYPE_1__*,char*,char*,int) ; 
 int /*<<< orphan*/  xo_failure (TYPE_1__*,char*,char*) ; 
 int xo_format_string_direct (TYPE_1__*,TYPE_2__*,int,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static ssize_t
xo_format_gettext (xo_handle_t *xop, xo_xff_flags_t flags,
		   ssize_t start_offset, ssize_t cols, int need_enc)
{
    xo_buffer_t *xbp = &xop->xo_data;

    if (!xo_buf_has_room(xbp, 1))
	return cols;

    xbp->xb_curp[0] = '\0'; /* NUL-terminate the input string */
    
    char *cp = xbp->xb_bufp + start_offset;
    ssize_t len = xbp->xb_curp - cp;
    const char *newstr = NULL;

    /*
     * The plural flag asks us to look backwards at the last numeric
     * value rendered and disect the string into two pieces.
     */
    if (flags & XFF_GT_PLURAL) {
	int n = xo_buf_find_last_number(xbp, start_offset);
	char *two = memchr(cp, (int) ',', len);
	if (two == NULL) {
	    xo_failure(xop, "no comma in plural gettext field: '%s'", cp);
	    return cols;
	}

	if (two == cp) {
	    xo_failure(xop, "nothing before comma in plural gettext "
		       "field: '%s'", cp);
	    return cols;
	}

	if (two == xbp->xb_curp) {
	    xo_failure(xop, "nothing after comma in plural gettext "
		       "field: '%s'", cp);
	    return cols;
	}

	*two++ = '\0';
	if (flags & XFF_GT_FIELD) {
	    newstr = xo_dngettext(xop, cp, two, n);
	} else {
	    /* Don't do a gettext() look up, just get the plural form */
	    newstr = (n == 1) ? cp : two;
	}

	/*
	 * If we returned the first string, optimize a bit by
	 * backing up over comma
	 */
	if (newstr == cp) {
	    xbp->xb_curp = two - 1; /* One for comma */
	    /*
	     * If the caller wanted UTF8, we're done; nothing changed,
	     * but we need to count the columns used.
	     */
	    if (need_enc == XF_ENC_UTF8)
		return xo_count_utf8_cols(cp, xbp->xb_curp - cp);
	}

    } else {
	/* The simple case (singular) */
	newstr = xo_dgettext(xop, cp);

	if (newstr == cp) {
	    /* If the caller wanted UTF8, we're done; nothing changed */
	    if (need_enc == XF_ENC_UTF8)
		return cols;
	}
    }

    /*
     * Since the new string string might be in gettext's buffer or
     * in the buffer (as the plural form), we make a copy.
     */
    ssize_t nlen = strlen(newstr);
    char *newcopy = alloca(nlen + 1);
    memcpy(newcopy, newstr, nlen + 1);

    xbp->xb_curp = xbp->xb_bufp + start_offset; /* Reset the buffer */
    return xo_format_string_direct(xop, xbp, flags, NULL, newcopy, nlen, 0,
				   need_enc, XF_ENC_UTF8);
}