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
typedef  size_t uint ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LC_ALL ; 
 int all_charmaps ; 
 int all_locales ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 TYPE_1__* kwinfo ; 
 int /*<<< orphan*/  list_charmaps () ; 
 int /*<<< orphan*/  list_locales () ; 
 size_t nitems (TYPE_1__*) ; 
 scalar_t__ optind ; 
 int prt_categories ; 
 int prt_keywords ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  showdetails (char*) ; 
 int /*<<< orphan*/  showkeywordslist (char*) ; 
 int /*<<< orphan*/  showlocale () ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	int	ch;
	int	tmp;

	while ((ch = getopt(argc, argv, "ackms:")) != -1) {
		switch (ch) {
		case 'a':
			all_locales = 1;
			break;
		case 'c':
			prt_categories = 1;
			break;
		case 'k':
			prt_keywords = 1;
			break;
		case 'm':
			all_charmaps = 1;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	/* validate arguments */
	if (all_locales && all_charmaps)
		usage();
	if ((all_locales || all_charmaps) && argc > 0)
		usage();
	if ((all_locales || all_charmaps) && (prt_categories || prt_keywords))
		usage();

	/* process '-a' */
	if (all_locales) {
		list_locales();
		exit(0);
	}

	/* process '-m' */
	if (all_charmaps) {
		list_charmaps();
		exit(0);
	}

	/* check for special case '-k list' */
	tmp = 0;
	if (prt_keywords && argc > 0)
		while (tmp < argc)
			if (strcasecmp(argv[tmp++], "list") == 0) {
				showkeywordslist(argv[tmp]);
				exit(0);
			}

	/* process '-c', '-k', or command line arguments. */
	if (prt_categories || prt_keywords || argc > 0) {
		if (prt_keywords || argc > 0)
			setlocale(LC_ALL, "");
		if (argc > 0) {
			while (argc > 0) {
				showdetails(*argv);
				argv++;
				argc--;
			}
		} else {
			uint i;
			for (i = 0; i < nitems(kwinfo); i++)
				showdetails(kwinfo[i].name);
		}
		exit(0);
	}

	/* no arguments, show current locale state */
	showlocale();

	return (0);
}