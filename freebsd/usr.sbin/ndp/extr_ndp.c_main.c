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
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  delete (char*) ; 
 int /*<<< orphan*/  dump (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  file (char*) ; 
 int /*<<< orphan*/  get (char*) ; 
 int /*<<< orphan*/  getdefif () ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  gmt2local (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  harmonize_rtr () ; 
 int /*<<< orphan*/  if_nametoindex (char*) ; 
 int /*<<< orphan*/  ifinfo (char*,int,char**) ; 
 int nflag ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  pfx_flush () ; 
 int /*<<< orphan*/  pid ; 
 int /*<<< orphan*/  plist () ; 
 int /*<<< orphan*/  repeat ; 
 int /*<<< orphan*/  rtr_flush () ; 
 int /*<<< orphan*/  rtrlist () ; 
 int /*<<< orphan*/  set (int,char**) ; 
 int /*<<< orphan*/  setdefif (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int tflag ; 
 int /*<<< orphan*/  thiszone ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	int ch, mode = 0;
	char *arg = NULL;

	pid = getpid();
	thiszone = gmt2local(0);
	while ((ch = getopt(argc, argv, "acd:f:Ii:nprstA:HPR")) != -1)
		switch (ch) {
		case 'a':
		case 'c':
		case 'p':
		case 'r':
		case 'H':
		case 'P':
		case 'R':
		case 's':
		case 'I':
			if (mode) {
				usage();
				/*NOTREACHED*/
			}
			mode = ch;
			arg = NULL;
			break;
		case 'f':
			exit(file(optarg) ? 1 : 0);
		case 'd':
		case 'i':
			if (mode) {
				usage();
				/*NOTREACHED*/
			}
			mode = ch;
			arg = optarg;
			break;
		case 'n':
			nflag = 1;
			break;
		case 't':
			tflag = 1;
			break;
		case 'A':
			if (mode) {
				usage();
				/*NOTREACHED*/
			}
			mode = 'a';
			repeat = atoi(optarg);
			if (repeat < 0) {
				usage();
				/*NOTREACHED*/
			}
			break;
		default:
			usage();
		}

	argc -= optind;
	argv += optind;

	switch (mode) {
	case 'a':
	case 'c':
		if (argc != 0) {
			usage();
			/*NOTREACHED*/
		}
		dump(0, mode == 'c');
		break;
	case 'd':
		if (argc != 0) {
			usage();
			/*NOTREACHED*/
		}
		delete(arg);
		break;
	case 'I':
#ifdef SIOCSDEFIFACE_IN6	/* XXX: check SIOCGDEFIFACE_IN6 as well? */
		if (argc > 1) {
			usage();
			/*NOTREACHED*/
		} else if (argc == 1) {
			if (strcmp(*argv, "delete") == 0 ||
			    if_nametoindex(*argv))
				setdefif(*argv);
			else
				errx(1, "invalid interface %s", *argv);
		}
		getdefif(); /* always call it to print the result */
		break;
#else
		errx(1, "not supported yet");
		/*NOTREACHED*/
#endif
	case 'p':
		if (argc != 0) {
			usage();
			/*NOTREACHED*/
		}
		plist();
		break;
	case 'i':
		ifinfo(arg, argc, argv);
		break;
	case 'r':
		if (argc != 0) {
			usage();
			/*NOTREACHED*/
		}
		rtrlist();
		break;
	case 's':
		if (argc < 2 || argc > 4)
			usage();
		exit(set(argc, argv) ? 1 : 0);
	case 'H':
		if (argc != 0) {
			usage();
			/*NOTREACHED*/
		}
		harmonize_rtr();
		break;
	case 'P':
		if (argc != 0) {
			usage();
			/*NOTREACHED*/
		}
		pfx_flush();
		break;
	case 'R':
		if (argc != 0) {
			usage();
			/*NOTREACHED*/
		}
		rtr_flush();
		break;
	case 0:
		if (argc != 1) {
			usage();
			/*NOTREACHED*/
		}
		get(argv[0]);
		break;
	}
	exit(0);
}