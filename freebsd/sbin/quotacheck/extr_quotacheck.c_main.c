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
typedef  int /*<<< orphan*/  u_long ;
struct quotafile {int dummy; } ;
struct passwd {int /*<<< orphan*/  pw_name; scalar_t__ pw_uid; } ;
struct group {int /*<<< orphan*/  gr_name; scalar_t__ gr_gid; } ;
struct fstab {int /*<<< orphan*/  fs_spec; int /*<<< orphan*/  fs_file; } ;

/* Variables and functions */
 char* FSTAB ; 
 int /*<<< orphan*/  GRPQUOTA ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  USRQUOTA ; 
 int /*<<< orphan*/  addid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ aflag ; 
 int atoi (int /*<<< orphan*/ ) ; 
 char* blockcheck (int /*<<< orphan*/ ) ; 
 int cflag ; 
 int checkfstab (scalar_t__,scalar_t__) ; 
 scalar_t__ chkquota (char*,struct quotafile*,struct quotafile*) ; 
 int /*<<< orphan*/  endfsent () ; 
 int /*<<< orphan*/  endgrent () ; 
 int /*<<< orphan*/  endpwent () ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 struct fstab* getfsent () ; 
 struct group* getgrent () ; 
 int getopt (int,char**,char*) ; 
 struct passwd* getpwent () ; 
 scalar_t__ gflag ; 
 int oneof (int /*<<< orphan*/ ,char**,int) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  quota_close (struct quotafile*) ; 
 struct quotafile* quota_open (struct fstab*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ setfsent () ; 
 int /*<<< orphan*/  setgrent () ; 
 int /*<<< orphan*/  setpwent () ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ uflag ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  vflag ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
main(int argc, char *argv[])
{
	struct fstab *fs;
	struct passwd *pw;
	struct group *gr;
	struct quotafile *qfu, *qfg;
	int i, argnum, maxrun, errs, ch;
	long done = 0;
	char *name;

	errs = maxrun = 0;
	while ((ch = getopt(argc, argv, "ac:guvl:")) != -1) {
		switch(ch) {
		case 'a':
			aflag++;
			break;
		case 'c':
			if (cflag)
				usage();
			cflag = atoi(optarg);
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
		case 'l':
			maxrun = atoi(optarg);
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;
	if ((argc == 0 && !aflag) || (argc > 0 && aflag))
		usage();
	if (cflag && cflag != 32 && cflag != 64)
		usage();
	if (!gflag && !uflag) {
		gflag++;
		uflag++;
	}
	if (gflag) {
		setgrent();
		while ((gr = getgrent()) != NULL)
			(void) addid((u_long)gr->gr_gid, GRPQUOTA, gr->gr_name,
			    NULL);
		endgrent();
	}
	if (uflag) {
		setpwent();
		while ((pw = getpwent()) != NULL)
			(void) addid((u_long)pw->pw_uid, USRQUOTA, pw->pw_name,
			    NULL);
		endpwent();
	}
	/*
	 * The maxrun (-l) option is now deprecated.
	 */
	if (maxrun > 0)
		warnx("the -l option is now deprecated");
	if (aflag)
		exit(checkfstab(uflag, gflag));
	if (setfsent() == 0)
		errx(1, "%s: can't open", FSTAB);
	while ((fs = getfsent()) != NULL) {
		if (((argnum = oneof(fs->fs_file, argv, argc)) >= 0 ||
		     (argnum = oneof(fs->fs_spec, argv, argc)) >= 0) &&
		    (name = blockcheck(fs->fs_spec))) {
			done |= 1 << argnum;
			qfu = NULL;
			if (uflag)
				qfu = quota_open(fs, USRQUOTA, O_CREAT|O_RDWR);
			qfg = NULL;
			if (gflag)
				qfg = quota_open(fs, GRPQUOTA, O_CREAT|O_RDWR);
			if (qfu == NULL && qfg == NULL)
				continue;
			errs += chkquota(name, qfu, qfg);
			if (qfu)
				quota_close(qfu);
			if (qfg)
				quota_close(qfg);
		}
	}
	endfsent();
	for (i = 0; i < argc; i++)
		if ((done & (1 << i)) == 0)
			fprintf(stderr, "%s not found in %s\n",
				argv[i], FSTAB);
	exit(errs);
}