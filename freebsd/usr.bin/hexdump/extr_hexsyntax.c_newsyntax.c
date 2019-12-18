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
 int /*<<< orphan*/  ALL ; 
 int /*<<< orphan*/  add (char*) ; 
 int /*<<< orphan*/  addfile (char*) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  fshead ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  length ; 
 char* optarg ; 
 int /*<<< orphan*/  optind ; 
 int skip ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strrchr (char*,char) ; 
 int strtoll (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  vflag ; 

void
newsyntax(int argc, char ***argvp)
{
	int ch;
	char *p, **argv;

	argv = *argvp;
	if ((p = strrchr(argv[0], 'h')) != NULL &&
	    strcmp(p, "hd") == 0) {
		/* "Canonical" format, implies -C. */
		add("\"%08.8_Ax\n\"");
		add("\"%08.8_ax  \" 8/1 \"%02x \" \"  \" 8/1 \"%02x \" ");
		add("\"  |\" 16/1 \"%_p\" \"|\\n\"");
	}
	while ((ch = getopt(argc, argv, "bcCde:f:n:os:vx")) != -1)
		switch (ch) {
		case 'b':
			add("\"%07.7_Ax\n\"");
			add("\"%07.7_ax \" 16/1 \"%03o \" \"\\n\"");
			break;
		case 'c':
			add("\"%07.7_Ax\n\"");
			add("\"%07.7_ax \" 16/1 \"%3_c \" \"\\n\"");
			break;
		case 'C':
			add("\"%08.8_Ax\n\"");
			add("\"%08.8_ax  \" 8/1 \"%02x \" \"  \" 8/1 \"%02x \" ");
			add("\"  |\" 16/1 \"%_p\" \"|\\n\"");
			break;
		case 'd':
			add("\"%07.7_Ax\n\"");
			add("\"%07.7_ax \" 8/2 \"  %05u \" \"\\n\"");
			break;
		case 'e':
			add(optarg);
			break;
		case 'f':
			addfile(optarg);
			break;
		case 'n':
			if ((length = atoi(optarg)) < 0)
				errx(1, "%s: bad length value", optarg);
			break;
		case 'o':
			add("\"%07.7_Ax\n\"");
			add("\"%07.7_ax \" 8/2 \" %06o \" \"\\n\"");
			break;
		case 's':
			if ((skip = strtoll(optarg, &p, 0)) < 0)
				errx(1, "%s: bad skip value", optarg);
			switch(*p) {
			case 'b':
				skip *= 512;
				break;
			case 'k':
				skip *= 1024;
				break;
			case 'm':
				skip *= 1048576;
				break;
			}
			break;
		case 'v':
			vflag = ALL;
			break;
		case 'x':
			add("\"%07.7_Ax\n\"");
			add("\"%07.7_ax \" 8/2 \"   %04x \" \"\\n\"");
			break;
		case '?':
			usage();
		}

	if (!fshead) {
		add("\"%07.7_Ax\n\"");
		add("\"%07.7_ax \" 8/2 \"%04x \" \"\\n\"");
	}

	*argvp += optind;
}