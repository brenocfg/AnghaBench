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
typedef  scalar_t__ xo_xof_flags_t ;
typedef  int /*<<< orphan*/  xo_handle_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  XOF_CLEAR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOF_COLOR_ALLOWED ; 
 int /*<<< orphan*/  XOF_SET (int /*<<< orphan*/ *,scalar_t__) ; 
 char* alloca (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* strchr (char*,char) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  xo_failure (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ xo_name_lookup (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xo_set_color_map (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ xo_streq (char*,char*) ; 
 int /*<<< orphan*/  xo_xof_simple_names ; 

__attribute__((used)) static int
xo_set_options_simple (xo_handle_t *xop, const char *input)
{
    xo_xof_flags_t new_flag;
    char *cp, *ep, *vp, *np, *bp;
    ssize_t len = strlen(input) + 1;

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

	new_flag = xo_name_lookup(xo_xof_simple_names, cp, -1);
	if (new_flag != 0) {
	    XOF_SET(xop, new_flag);
	} else if (xo_streq(cp, "no-color")) {
	    XOF_CLEAR(xop, XOF_COLOR_ALLOWED);
	} else {
	    xo_failure(xop, "unknown simple option: %s", cp);
	    return -1;
	}
    }

    return 0;
}