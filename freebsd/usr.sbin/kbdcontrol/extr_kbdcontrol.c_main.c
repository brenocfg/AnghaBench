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
 int /*<<< orphan*/  KBADDKBD ; 
 int /*<<< orphan*/  KBRELKBD ; 
 int /*<<< orphan*/  add_keymap_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char const*) ; 
 int hex ; 
 int /*<<< orphan*/  load_default_functionkeys () ; 
 int /*<<< orphan*/  load_keymap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mux_keyboard (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nextarg (int,char**,int*,float) ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int optreset ; 
 int /*<<< orphan*/  print_keymap () ; 
 int /*<<< orphan*/  release_keyboard () ; 
 int /*<<< orphan*/  set_bell_values (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_functionkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_keyboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_keyrates (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_kbd_info () ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	const char	*optstring = "A:a:b:df:iKk:Fl:L:P:r:x";
	int		opt;

	/* Collect any -P arguments, regardless of where they appear. */
	while ((opt = getopt(argc, argv, optstring)) != -1) {
		if (opt == 'P')
			add_keymap_path(optarg);
		if (opt == '?')
			usage();
	}

	optind = optreset = 1;
	while ((opt = getopt(argc, argv, optstring)) != -1)
		switch(opt) {
		case 'A':
		case 'a':
			mux_keyboard((opt == 'A')? KBRELKBD : KBADDKBD, optarg);
			break;
		case 'b':
			set_bell_values(optarg);
			break;
		case 'd':
			print_keymap();
			break;
		case 'l':
			load_keymap(optarg, 0);
			break;
		case 'L':
			load_keymap(optarg, 1);
			break;
		case 'P':
			break;
		case 'f':
			set_functionkey(optarg,
			    nextarg(argc, argv, &optind, 'f'));
			break;
		case 'F':
			load_default_functionkeys();
			break;
		case 'i':
			show_kbd_info();
			break;
		case 'K':
			release_keyboard();
			break;
		case 'k':
			set_keyboard(optarg);
			break;
		case 'r':
			set_keyrates(optarg);
			break;
		case 'x':
			hex = 1;
			break;
		default:
			usage();
		}
	if ((optind != argc) || (argc == 1))
		usage();
	exit(0);
}