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
 int DUMP_ALL ; 
 int DUMP_FBF ; 
 int DUMP_FMT_RAW ; 
 int DUMP_FMT_TXT ; 
 int /*<<< orphan*/  clear_history () ; 
 int /*<<< orphan*/  dump_screen (int,int) ; 
 int /*<<< orphan*/  get_terminal_emulators () ; 
 int getopt (int,char**,char const*) ; 
 int hex ; 
 int /*<<< orphan*/  init () ; 
 scalar_t__ is_vt4 () ; 
 int /*<<< orphan*/  load_default_scrnmap () ; 
 int /*<<< orphan*/  load_default_vt4font () ; 
 int /*<<< orphan*/  load_font (char*,char*) ; 
 int /*<<< orphan*/  load_scrnmap (char*) ; 
 char* nextarg (int,char**,int*,float,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  print_scrnmap () ; 
 int /*<<< orphan*/  revert () ; 
 int /*<<< orphan*/  set_border_color (char*) ; 
 int /*<<< orphan*/  set_console (char*) ; 
 int /*<<< orphan*/  set_cursor_type (char*) ; 
 int /*<<< orphan*/  set_history (char*) ; 
 int /*<<< orphan*/  set_lockswitch (char*) ; 
 int /*<<< orphan*/  set_mouse (char*) ; 
 int /*<<< orphan*/  set_mouse_char (char*) ; 
 int /*<<< orphan*/  set_normal_colors (int,char**,int*) ; 
 int /*<<< orphan*/  set_reverse_colors (int,char**,int*) ; 
 int /*<<< orphan*/  set_screensaver_timeout (char*) ; 
 int /*<<< orphan*/  set_terminal_emulator (char*) ; 
 int /*<<< orphan*/  set_terminal_mode (char*) ; 
 int /*<<< orphan*/  show_info (char*) ; 
 int sscanf (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  test_frame () ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  vesa_cols ; 
 int /*<<< orphan*/  vesa_rows ; 
 int /*<<< orphan*/  video_mode (int,char**,int*) ; 
 scalar_t__ vt4_mode ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
main(int argc, char **argv)
{
	char    *font, *type, *termmode;
	const char *opts;
	int	dumpmod, dumpopt, opt;

	vt4_mode = is_vt4();

	init();

	dumpmod = 0;
	dumpopt = DUMP_FBF;
	termmode = NULL;
	if (vt4_mode)
		opts = "b:Cc:fg:h:Hi:M:m:pPr:S:s:T:t:x";
	else
		opts = "b:Cc:deE:fg:h:Hi:l:LM:m:pPr:S:s:T:t:x";

	while ((opt = getopt(argc, argv, opts)) != -1)
		switch(opt) {
		case 'b':
			set_border_color(optarg);
			break;
		case 'C':
			clear_history();
			break;
		case 'c':
			set_cursor_type(optarg);
			break;
		case 'd':
			if (vt4_mode)
				break;
			print_scrnmap();
			break;
		case 'E':
			if (vt4_mode)
				break;
			set_terminal_emulator(optarg);
			break;
		case 'e':
			if (vt4_mode)
				break;
			get_terminal_emulators();
			break;
		case 'f':
			optarg = nextarg(argc, argv, &optind, 'f', 0);
			if (optarg != NULL) {
				font = nextarg(argc, argv, &optind, 'f', 0);

				if (font == NULL) {
					type = NULL;
					font = optarg;
				} else
					type = optarg;

				load_font(type, font);
			} else {
				if (!vt4_mode)
					usage(); /* Switch syscons to ROM? */

				load_default_vt4font();
			}
			break;
		case 'g':
			if (sscanf(optarg, "%dx%d",
			    &vesa_cols, &vesa_rows) != 2) {
				revert();
				warnx("incorrect geometry: %s", optarg);
				usage();
			}
                	break;
		case 'h':
			set_history(optarg);
			break;
		case 'H':
			dumpopt = DUMP_ALL;
			break;
		case 'i':
			show_info(optarg);
			break;
		case 'l':
			if (vt4_mode)
				break;
			load_scrnmap(optarg);
			break;
		case 'L':
			if (vt4_mode)
				break;
			load_default_scrnmap();
			break;
		case 'M':
			set_mouse_char(optarg);
			break;
		case 'm':
			set_mouse(optarg);
			break;
		case 'p':
			dumpmod = DUMP_FMT_RAW;
			break;
		case 'P':
			dumpmod = DUMP_FMT_TXT;
			break;
		case 'r':
			set_reverse_colors(argc, argv, &optind);
			break;
		case 'S':
			set_lockswitch(optarg);
			break;
		case 's':
			set_console(optarg);
			break;
		case 'T':
			if (strcmp(optarg, "xterm") != 0 &&
			    strcmp(optarg, "cons25") != 0)
				usage();
			termmode = optarg;
			break;
		case 't':
			set_screensaver_timeout(optarg);
			break;
		case 'x':
			hex = 1;
			break;
		default:
			usage();
		}

	if (dumpmod != 0)
		dump_screen(dumpmod, dumpopt);
	video_mode(argc, argv, &optind);
	set_normal_colors(argc, argv, &optind);

	if (optind < argc && !strcmp(argv[optind], "show")) {
		test_frame();
		optind++;
	}

	if (termmode != NULL)
		set_terminal_mode(termmode);

	if ((optind != argc) || (argc == 1))
		usage();
	return (0);
}