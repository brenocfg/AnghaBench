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
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvinum_attach (int,char* const*) ; 
 int /*<<< orphan*/  gvinum_concat (int,char* const*) ; 
 int /*<<< orphan*/  gvinum_create (int,char* const*) ; 
 int /*<<< orphan*/  gvinum_detach (int,char* const*) ; 
 int /*<<< orphan*/  gvinum_grow (int,char* const*) ; 
 int /*<<< orphan*/  gvinum_help () ; 
 int /*<<< orphan*/  gvinum_list (int,char* const*) ; 
 int /*<<< orphan*/  gvinum_mirror (int,char* const*) ; 
 int /*<<< orphan*/  gvinum_move (int,char* const*) ; 
 int /*<<< orphan*/  gvinum_parityop (int,char* const*,int) ; 
 int /*<<< orphan*/  gvinum_printconfig (int,char* const*) ; 
 int /*<<< orphan*/  gvinum_raid5 (int,char* const*) ; 
 int /*<<< orphan*/  gvinum_rename (int,char* const*) ; 
 int /*<<< orphan*/  gvinum_resetconfig (int,char* const*) ; 
 int /*<<< orphan*/  gvinum_rm (int,char* const*) ; 
 int /*<<< orphan*/  gvinum_saveconfig () ; 
 int /*<<< orphan*/  gvinum_setstate (int,char* const*) ; 
 int /*<<< orphan*/  gvinum_start (int,char* const*) ; 
 int /*<<< orphan*/  gvinum_stop (int,char* const*) ; 
 int /*<<< orphan*/  gvinum_stripe (int,char* const*) ; 
 int /*<<< orphan*/  printf (char*,char* const) ; 
 int /*<<< orphan*/  strcmp (char* const,char*) ; 

__attribute__((used)) static void
parseline(int argc, char * const *argv)
{

	if (argc <= 0)
		return;

	if (!strcmp(argv[0], "create"))
		gvinum_create(argc, argv);
	else if (!strcmp(argv[0], "exit") || !strcmp(argv[0], "quit"))
		exit(0);
	else if (!strcmp(argv[0], "attach"))
		gvinum_attach(argc, argv);
	else if (!strcmp(argv[0], "detach"))
		gvinum_detach(argc, argv);
	else if (!strcmp(argv[0], "concat"))
		gvinum_concat(argc, argv);
	else if (!strcmp(argv[0], "grow"))
		gvinum_grow(argc, argv);
	else if (!strcmp(argv[0], "help"))
		gvinum_help();
	else if (!strcmp(argv[0], "list") || !strcmp(argv[0], "l"))
		gvinum_list(argc, argv);
	else if (!strcmp(argv[0], "ld"))
		gvinum_list(argc, argv);
	else if (!strcmp(argv[0], "lp"))
		gvinum_list(argc, argv);
	else if (!strcmp(argv[0], "ls"))
		gvinum_list(argc, argv);
	else if (!strcmp(argv[0], "lv"))
		gvinum_list(argc, argv);
	else if (!strcmp(argv[0], "mirror"))
		gvinum_mirror(argc, argv);
	else if (!strcmp(argv[0], "move"))
		gvinum_move(argc, argv);
	else if (!strcmp(argv[0], "mv"))
		gvinum_move(argc, argv);
	else if (!strcmp(argv[0], "printconfig"))
		gvinum_printconfig(argc, argv);
	else if (!strcmp(argv[0], "raid5"))
		gvinum_raid5(argc, argv);
	else if (!strcmp(argv[0], "rename"))
		gvinum_rename(argc, argv);
	else if (!strcmp(argv[0], "resetconfig"))
		gvinum_resetconfig(argc, argv);
	else if (!strcmp(argv[0], "rm"))
		gvinum_rm(argc, argv);
	else if (!strcmp(argv[0], "saveconfig"))
		gvinum_saveconfig();
	else if (!strcmp(argv[0], "setstate"))
		gvinum_setstate(argc, argv);
	else if (!strcmp(argv[0], "start"))
		gvinum_start(argc, argv);
	else if (!strcmp(argv[0], "stop"))
		gvinum_stop(argc, argv);
	else if (!strcmp(argv[0], "stripe"))
		gvinum_stripe(argc, argv);
	else if (!strcmp(argv[0], "checkparity"))
		gvinum_parityop(argc, argv, 0);
	else if (!strcmp(argv[0], "rebuildparity"))
		gvinum_parityop(argc, argv, 1);
	else
		printf("unknown command '%s'\n", argv[0]);
}