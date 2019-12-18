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
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int NGROUPS ; 
 scalar_t__ alldigits (char*) ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  filename ; 
 scalar_t__ getgid () ; 
 int getgroups (int,scalar_t__*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  hflag ; 
 int /*<<< orphan*/  lflag ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  qflag ; 
 int /*<<< orphan*/  rflag ; 
 scalar_t__ showgid (scalar_t__) ; 
 scalar_t__ showgrpname (char*) ; 
 scalar_t__ showuid (scalar_t__) ; 
 scalar_t__ showusrname (char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  vflag ; 

int
main(int argc, char *argv[])
{
	int ngroups; 
	gid_t mygid, gidset[NGROUPS];
	int i, ch, gflag = 0, uflag = 0, errflag = 0;

	while ((ch = getopt(argc, argv, "f:ghlrquv")) != -1) {
		switch(ch) {
		case 'f':
			filename = optarg;
			break;
		case 'g':
			gflag++;
			break;
		case 'h':
			hflag++;
			break;
		case 'l':
			lflag++;
			break;
		case 'q':
			qflag++;
			break;
		case 'r':
			rflag++;
			break;
		case 'u':
			uflag++;
			break;
		case 'v':
			vflag++;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;
	if (!uflag && !gflag)
		uflag++;
	if (argc == 0) {
		if (uflag)
			errflag += showuid(getuid());
		if (gflag) {
			mygid = getgid();
			ngroups = getgroups(NGROUPS, gidset);
			if (ngroups < 0)
				err(1, "getgroups");
			errflag += showgid(mygid);
			for (i = 0; i < ngroups; i++)
				if (gidset[i] != mygid)
					errflag += showgid(gidset[i]);
		}
		return(errflag);
	}
	if (uflag && gflag)
		usage();
	if (uflag) {
		for (; argc > 0; argc--, argv++) {
			if (alldigits(*argv))
				errflag += showuid(atoi(*argv));
			else
				errflag += showusrname(*argv);
		}
		return(errflag);
	}
	if (gflag) {
		for (; argc > 0; argc--, argv++) {
			if (alldigits(*argv))
				errflag += showgid(atoi(*argv));
			else
				errflag += showgrpname(*argv);
		}
	}
	return(errflag);
}