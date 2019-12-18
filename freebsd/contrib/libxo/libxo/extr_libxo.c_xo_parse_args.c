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
typedef  int /*<<< orphan*/  xo_handle_t ;
typedef  int /*<<< orphan*/  libxo_opt ;
typedef  int /*<<< orphan*/  gnu_ext ;

/* Variables and functions */
 int /*<<< orphan*/  XOF_COLOR ; 
 int /*<<< orphan*/  XOF_COLOR_ALLOWED ; 
 scalar_t__ XOF_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOF_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XO_HAS_LIBXO ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ isatty (int) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/ * xo_default (int /*<<< orphan*/ *) ; 
 char* xo_program ; 
 scalar_t__ xo_set_options (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ xo_streq (char*,char const*) ; 
 int /*<<< orphan*/  xo_warnx (char*,...) ; 

int
xo_parse_args (int argc, char **argv)
{
    static char libxo_opt[] = "--libxo";
    char *cp;
    int i, save;

    /* Save our program name for xo_err and friends */
    xo_program = argv[0];
    cp = strrchr(xo_program, '/');
    if (cp)
	xo_program = ++cp;
    else
	cp = argv[0];		/* Reset to front of string */

    /* GNU tools add an annoying ".test" as the program extension; remove it */
    size_t len = strlen(xo_program);
    static const char gnu_ext[] = ".test";
    if (len >= sizeof(gnu_ext)) {
	cp += len + 1 - sizeof(gnu_ext);
	if (xo_streq(cp, gnu_ext))
	    *cp = '\0';
    }

    xo_handle_t *xop = xo_default(NULL);

    for (save = i = 1; i < argc; i++) {
	if (argv[i] == NULL
	    || strncmp(argv[i], libxo_opt, sizeof(libxo_opt) - 1) != 0) {
	    if (save != i)
		argv[save] = argv[i];
	    save += 1;
	    continue;
	}

	cp = argv[i] + sizeof(libxo_opt) - 1;
	if (*cp == '\0') {
	    cp = argv[++i];
	    if (cp == NULL) {
		xo_warnx("missing libxo option");
		return -1;
	    }
		
	    if (xo_set_options(xop, cp) < 0)
		return -1;
	} else if (*cp == ':') {
	    if (xo_set_options(xop, cp) < 0)
		return -1;

	} else if (*cp == '=') {
	    if (xo_set_options(xop, ++cp) < 0)
		return -1;

	} else if (*cp == '-') {
	    cp += 1;
	    if (xo_streq(cp, "check")) {
		exit(XO_HAS_LIBXO);

	    } else {
		xo_warnx("unknown libxo option: '%s'", argv[i]);
		return -1;
	    }
	} else {
		xo_warnx("unknown libxo option: '%s'", argv[i]);
	    return -1;
	}
    }

    /*
     * We only want to do color output on terminals, but we only want
     * to do this if the user has asked for color.
     */
    if (XOF_ISSET(xop, XOF_COLOR_ALLOWED) && isatty(1))
	XOF_SET(xop, XOF_COLOR);

    argv[save] = NULL;
    return save;
}