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
typedef  int /*<<< orphan*/  xo_emit_flags_t ;

/* Variables and functions */
 int /*<<< orphan*/  XOEF_RETAIN ; 
 int /*<<< orphan*/  XOF_COLOR ; 
 int /*<<< orphan*/  XOF_INFO ; 
 int /*<<< orphan*/  XOF_PRETTY ; 
 int /*<<< orphan*/  XOF_UNITS ; 
 int /*<<< orphan*/  XOF_XPATH ; 
 int /*<<< orphan*/  XO_STYLE_HTML ; 
 int /*<<< orphan*/  XO_STYLE_JSON ; 
 int /*<<< orphan*/  XO_STYLE_TEXT ; 
 int /*<<< orphan*/  XO_STYLE_XML ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 
 int /*<<< orphan*/  xo_close_container_h (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 
 int /*<<< orphan*/  xo_emit_f (int /*<<< orphan*/ ,char const*,char*,char*,char*,int,int) ; 
 int /*<<< orphan*/  xo_finish () ; 
 int /*<<< orphan*/  xo_open_container (char*) ; 
 int /*<<< orphan*/  xo_open_instance (char*) ; 
 int xo_parse_args (int,char**) ; 
 int /*<<< orphan*/  xo_set_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_set_style (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xo_streq (char*,char*) ; 

int
main (int argc, char **argv)
{
    int i, count = 10;
    int mon = 0;
    xo_emit_flags_t flags = XOEF_RETAIN;
    int opt_color = 1;

    argc = xo_parse_args(argc, argv);
    if (argc < 0)
	return 1;

    for (argc = 1; argv[argc]; argc++) {
	if (xo_streq(argv[argc], "xml"))
	    xo_set_style(NULL, XO_STYLE_XML);
	else if (xo_streq(argv[argc], "json"))
	    xo_set_style(NULL, XO_STYLE_JSON);
	else if (xo_streq(argv[argc], "text"))
	    xo_set_style(NULL, XO_STYLE_TEXT);
	else if (xo_streq(argv[argc], "html"))
	    xo_set_style(NULL, XO_STYLE_HTML);
	else if (xo_streq(argv[argc], "no-color"))
	    opt_color = 0;
	else if (xo_streq(argv[argc], "pretty"))
	    xo_set_flags(NULL, XOF_PRETTY);
	else if (xo_streq(argv[argc], "xpath"))
	    xo_set_flags(NULL, XOF_XPATH);
	else if (xo_streq(argv[argc], "info"))
	    xo_set_flags(NULL, XOF_INFO);
	else if (xo_streq(argv[argc], "no-retain"))
	    flags &= ~XOEF_RETAIN;
	else if (xo_streq(argv[argc], "big")) {
	    if (argv[argc + 1])
		count = atoi(argv[++argc]);
	}
    }

    xo_set_flags(NULL, XOF_UNITS); /* Always test w/ this */
    if (opt_color)
	xo_set_flags(NULL, XOF_COLOR); /* Force color output */
    xo_set_file(stdout);

    xo_open_container("top");
    xo_open_container("data");

    xo_emit("{C:fg-red,bg-green}Merry XMas!!{C:}\n");

    xo_emit("One {C:fg-yellow,bg-blue}{:animal}{C:}, "
	    "Two {C:fg-green,bg-yellow}{:animal}{C:}\n",
          "fish", "fish");

    const char *fmt1 = "The {C:fg-red}{k:name}{C:reset} is "
	"{C:/fg-%s}{:color}{C:reset} til {:time/%02d:%02d}\n";
    const char *fmt2 = "My {C:fg-red}{:hand}{C:reset} hand is "
	"{C:/fg-%s}{:color}{C:reset} til {:time/%02d:%02d}\n";

    for (i = 0; i < count; i++) {
	xo_open_instance("thing");
	xo_emit_f(flags, fmt1, "thing", "green", "green", 2, 15);
	xo_emit_f(flags, fmt2, "left", "blue", "blue", 3, 45);
    }

    xo_open_container("2by4");
    xo_emit("There is {:4x4} in {:2morrow}\n", "truck", "tomorrow");
    xo_close_container("2by4");


    xo_close_container("data");
    xo_close_container_h(NULL, "top");

    xo_finish();

    return 0;
}