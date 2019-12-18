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
 int /*<<< orphan*/  ARP_XO_VERSION ; 
 scalar_t__ ENXIO ; 
#define  F_DELETE 132 
#define  F_FILESET 131 
#define  F_GET 130 
#define  F_REPLACE 129 
#define  F_SET 128 
 int /*<<< orphan*/  SETFUNC (int) ; 
 int delete (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int file (char*) ; 
 int get (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  if_freenameindex (int /*<<< orphan*/ *) ; 
 scalar_t__ if_nametoindex (scalar_t__) ; 
 int /*<<< orphan*/ * ifnameindex ; 
 int nflag ; 
 int /*<<< orphan*/  nuke_entry ; 
 scalar_t__ optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  print_entry ; 
 scalar_t__ rifname ; 
 int /*<<< orphan*/  search (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set (int,char**) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_err (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  xo_errx (int,char*,...) ; 
 int /*<<< orphan*/  xo_finish () ; 
 int /*<<< orphan*/  xo_open_container (char*) ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 
 int xo_parse_args (int,char**) ; 
 int /*<<< orphan*/  xo_set_version (int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	int ch, func = 0;
	int rtn = 0;
	int aflag = 0;	/* do it for all entries */

	argc = xo_parse_args(argc, argv);
	if (argc < 0)
		exit(1);

	while ((ch = getopt(argc, argv, "andfsSi:")) != -1)
		switch(ch) {
		case 'a':
			aflag = 1;
			break;
		case 'd':
			SETFUNC(F_DELETE);
			break;
		case 'n':
			nflag = 1;
			break;
		case 'S':
			SETFUNC(F_REPLACE);
			break;
		case 's':
			SETFUNC(F_SET);
			break;
		case 'f' :
			SETFUNC(F_FILESET);
			break;
		case 'i':
			rifname = optarg;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (!func)
		func = F_GET;
	if (rifname) {
		if (func != F_GET && !(func == F_DELETE && aflag))
			xo_errx(1, "-i not applicable to this operation");
		if (if_nametoindex(rifname) == 0) {
			if (errno == ENXIO)
				xo_errx(1, "interface %s does not exist",
				    rifname);
			else
				xo_err(1, "if_nametoindex(%s)", rifname);
		}
	}
	switch (func) {
	case F_GET:
		if (aflag) {
			if (argc != 0)
				usage();

			xo_set_version(ARP_XO_VERSION);
			xo_open_container("arp");
			xo_open_list("arp-cache");

			search(0, print_entry);

			xo_close_list("arp-cache");
			xo_close_container("arp");
			xo_finish();
		} else {
			if (argc != 1)
				usage();
			rtn = get(argv[0]);
		}
		break;
	case F_SET:
	case F_REPLACE:
		if (argc < 2 || argc > 6)
			usage();
		if (func == F_REPLACE)
			(void)delete(argv[0]);
		rtn = set(argc, argv) ? 1 : 0;
		break;
	case F_DELETE:
		if (aflag) {
			if (argc != 0)
				usage();
			search(0, nuke_entry);
		} else {
			if (argc != 1)
				usage();
			rtn = delete(argv[0]);
		}
		break;
	case F_FILESET:
		if (argc != 1)
			usage();
		rtn = file(argv[0]);
		break;
	}

	if (ifnameindex != NULL)
		if_freenameindex(ifnameindex);

	return (rtn);
}