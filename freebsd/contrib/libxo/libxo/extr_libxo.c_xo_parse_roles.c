#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int xo_xff_flags_t ;
typedef  int /*<<< orphan*/  xo_handle_t ;
struct TYPE_3__ {int xfi_flags; char xfi_ftype; int xfi_fnum; } ;
typedef  TYPE_1__ xo_field_info_t ;
typedef  int uint8_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int XFF_ARGUMENT ; 
 int XFF_COLON ; 
 int XFF_DISPLAY_ONLY ; 
 int XFF_ENCODE_ONLY ; 
 int XFF_GT_FIELD ; 
 int XFF_GT_PLURAL ; 
 int XFF_HUMANIZE ; 
 int XFF_KEY ; 
 int XFF_LEAF_LIST ; 
 int XFF_NOQUOTE ; 
 int XFF_QUOTE ; 
 int XFF_TRIM_WS ; 
 int XFF_WS ; 
 int /*<<< orphan*/  xo_failure (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  xo_modifier_names ; 
 int xo_name_lookup (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 int /*<<< orphan*/  xo_printable (char const*) ; 
 int /*<<< orphan*/  xo_role_names ; 

__attribute__((used)) static const char *
xo_parse_roles (xo_handle_t *xop, const char *fmt,
		const char *basep, xo_field_info_t *xfip)
{
    const char *sp;
    unsigned ftype = 0;
    xo_xff_flags_t flags = 0;
    uint8_t fnum = 0;

    for (sp = basep; sp && *sp; sp++) {
	if (*sp == ':' || *sp == '/' || *sp == '}')
	    break;

	if (*sp == '\\') {
	    if (sp[1] == '\0') {
		xo_failure(xop, "backslash at the end of string");
		return NULL;
	    }

	    /* Anything backslashed is ignored */
	    sp += 1;
	    continue;
	}

	if (*sp == ',') {
	    const char *np;
	    for (np = ++sp; *np; np++)
		if (*np == ':' || *np == '/' || *np == '}' || *np == ',')
		    break;

	    ssize_t slen = np - sp;
	    if (slen > 0) {
		xo_xff_flags_t value;

		value = xo_name_lookup(xo_role_names, sp, slen);
		if (value)
		    ftype = value;
		else {
		    value = xo_name_lookup(xo_modifier_names, sp, slen);
		    if (value)
			flags |= value;
		    else
			xo_failure(xop, "unknown keyword ignored: '%.*s'",
				   slen, sp);
		}
	    }

	    sp = np - 1;
	    continue;
	}

	switch (*sp) {
	case 'C':
	case 'D':
	case 'E':
	case 'G':
	case 'L':
	case 'N':
	case 'P':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case '[':
	case ']':
	    if (ftype != 0) {
		xo_failure(xop, "field descriptor uses multiple types: '%s'",
			   xo_printable(fmt));
		return NULL;
	    }
	    ftype = *sp;
	    break;

	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	    fnum = (fnum * 10) + (*sp - '0');
	    break;

	case 'a':
	    flags |= XFF_ARGUMENT;
	    break;

	case 'c':
	    flags |= XFF_COLON;
	    break;

	case 'd':
	    flags |= XFF_DISPLAY_ONLY;
	    break;

	case 'e':
	    flags |= XFF_ENCODE_ONLY;
	    break;

	case 'g':
	    flags |= XFF_GT_FIELD;
	    break;

	case 'h':
	    flags |= XFF_HUMANIZE;
	    break;

	case 'k':
	    flags |= XFF_KEY;
	    break;

	case 'l':
	    flags |= XFF_LEAF_LIST;
	    break;

	case 'n':
	    flags |= XFF_NOQUOTE;
	    break;

	case 'p':
	    flags |= XFF_GT_PLURAL;
	    break;

	case 'q':
	    flags |= XFF_QUOTE;
	    break;

	case 't':
	    flags |= XFF_TRIM_WS;
	    break;

	case 'w':
	    flags |= XFF_WS;
	    break;

	default:
	    xo_failure(xop, "field descriptor uses unknown modifier: '%s'",
		       xo_printable(fmt));
	    /*
	     * No good answer here; a bad format will likely
	     * mean a core file.  We just return and hope
	     * the caller notices there's no output, and while
	     * that seems, well, bad, there's nothing better.
	     */
	    return NULL;
	}

	if (ftype == 'N' || ftype == 'U') {
	    if (flags & XFF_COLON) {
		xo_failure(xop, "colon modifier on 'N' or 'U' field ignored: "
			   "'%s'", xo_printable(fmt));
		flags &= ~XFF_COLON;
	    }
	}
    }

    xfip->xfi_flags = flags;
    xfip->xfi_ftype = ftype ?: 'V';
    xfip->xfi_fnum = fnum;

    return sp;
}