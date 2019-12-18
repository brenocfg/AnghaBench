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
struct fstab {char const* fs_vfstype; char const* fs_type; int /*<<< orphan*/  fs_spec; int /*<<< orphan*/  fs_file; } ;

/* Variables and functions */
 char* FSTAB_RW ; 
 int /*<<< orphan*/  GRPQUOTA ; 
 int /*<<< orphan*/  USRQUOTA ; 
 scalar_t__ aflag ; 
 int /*<<< orphan*/  endfsent () ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 struct fstab* getfsent () ; 
 int getopt (int,char**,char*) ; 
 char* getprogname () ; 
 scalar_t__ gflag ; 
 long oneof (int /*<<< orphan*/ ,char**,int) ; 
 scalar_t__ optind ; 
 scalar_t__ quotaonoff (struct fstab*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setfsent () ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ uflag ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  vflag ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
main(int argc, char **argv)
{
	struct fstab *fs;
	const char *whoami;
	long argnum, done = 0;
	int ch, i, offmode = 0, errs = 0;

	whoami = getprogname();
	if (strcmp(whoami, "quotaoff") == 0)
		offmode++;
	else if (strcmp(whoami, "quotaon") != 0)
		errx(1, "name must be quotaon or quotaoff");
	while ((ch = getopt(argc, argv, "avug")) != -1) {
		switch(ch) {
		case 'a':
			aflag++;
			break;
		case 'g':
			gflag++;
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
	if (argc <= 0 && !aflag)
		usage();
	if (!gflag && !uflag) {
		gflag++;
		uflag++;
	}
	setfsent();
	while ((fs = getfsent()) != NULL) {
		if (strcmp(fs->fs_vfstype, "ufs") ||
		    strcmp(fs->fs_type, FSTAB_RW))
			continue;
		if (aflag) {
			if (gflag)
				errs += quotaonoff(fs, offmode, GRPQUOTA);
			if (uflag)
				errs += quotaonoff(fs, offmode, USRQUOTA);
			continue;
		}
		if ((argnum = oneof(fs->fs_file, argv, argc)) >= 0 ||
		    (argnum = oneof(fs->fs_spec, argv, argc)) >= 0) {
			done |= 1 << argnum;
			if (gflag)
				errs += quotaonoff(fs, offmode, GRPQUOTA);
			if (uflag)
				errs += quotaonoff(fs, offmode, USRQUOTA);
		}
	}
	endfsent();
	for (i = 0; i < argc; i++)
		if ((done & (1 << i)) == 0)
			warnx("%s not found in fstab", argv[i]);
	exit(errs);
}