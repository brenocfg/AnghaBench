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

/* Variables and functions */
 int /*<<< orphan*/ * DEFAULT_SC_FONT ; 
 int /*<<< orphan*/  DEFAULT_SC_FONT_DIR ; 
 int /*<<< orphan*/  DEFAULT_SC_KEYMAP_DIR ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 scalar_t__ check_vt () ; 
 int /*<<< orphan*/  dir ; 
 int /*<<< orphan*/  extract_name (char*) ; 
 int /*<<< orphan*/ * font_current ; 
 int /*<<< orphan*/ * font_default ; 
 int /*<<< orphan*/  fontdir ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * get_font () ; 
 int /*<<< orphan*/  get_locale () ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  keymapdir ; 
 int /*<<< orphan*/  lang ; 
 int /*<<< orphan*/  menu_read () ; 
 int /*<<< orphan*/  parse_args (int,char**) ; 
 int /*<<< orphan*/  program ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ system (char*) ; 
 scalar_t__ using_vt ; 
 scalar_t__ x11 ; 

int
main(int argc, char **argv)
{

	x11 = system("kbdcontrol -d >/dev/null");

	if (x11) {
		fprintf(stderr, "You are not on a virtual console - "
				"expect certain strange side-effects\n");
		sleep(2);
	}

	using_vt = check_vt();
	if (using_vt == 0) {
		keymapdir = DEFAULT_SC_KEYMAP_DIR;
		fontdir = DEFAULT_SC_FONT_DIR;
		font_default = DEFAULT_SC_FONT;
	}

	SLIST_INIT(&head);

	lang = get_locale();

	program = extract_name(argv[0]);

	font_current = get_font();
	if (font_current == NULL)
		font_current = font_default;

	if (strcmp(program, "kbdmap"))
		dir = fontdir;
	else
		dir = keymapdir;

	/* Parse command line arguments */
	parse_args(argc, argv);

	/* Read and display options */
	menu_read();

	return 0;
}