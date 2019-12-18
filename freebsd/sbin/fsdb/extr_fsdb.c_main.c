#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* fs_fsmnt; scalar_t__ fs_clean; } ;

/* Variables and functions */
 int /*<<< orphan*/  ckfini (int /*<<< orphan*/ ) ; 
 int cmdloop () ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ nflag ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sbdirty () ; 
 TYPE_1__ sblock ; 
 int /*<<< orphan*/  sblock_init () ; 
 int /*<<< orphan*/  setup (char*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	int ch, rval;
	char *fsys = NULL;

	while (-1 != (ch = getopt(argc, argv, "fdr"))) {
		switch (ch) {
		case 'f':
			/* The -f option is left for historical
			 * reasons and has no meaning.
			 */
			break;
		case 'd':
			debug++;
			break;
		case 'r':
			nflag++; /* "no" in fsck, readonly for us */
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;
	if (argc != 1)
		usage();
	else
		fsys = argv[0];

	sblock_init();
	if (!setup(fsys))
		errx(1, "cannot set up file system `%s'", fsys);
	printf("%s file system `%s'\nLast Mounted on %s\n",
	       nflag? "Examining": "Editing", fsys, sblock.fs_fsmnt);
	rval = cmdloop();
	if (!nflag) {
		sblock.fs_clean = 0;	/* mark it dirty */
		sbdirty();
		ckfini(0);
		printf("*** FILE SYSTEM MARKED DIRTY\n");
		printf("*** BE SURE TO RUN FSCK TO CLEAN UP ANY DAMAGE\n");
		printf("*** IF IT WAS MOUNTED, RE-MOUNT WITH -u -o reload\n");
	}
	exit(rval);
}