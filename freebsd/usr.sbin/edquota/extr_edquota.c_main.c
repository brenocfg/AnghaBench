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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uid_t ;
struct TYPE_2__ {scalar_t__ dqb_itime; scalar_t__ dqb_btime; void* dqb_ihardlimit; void* dqb_isoftlimit; void* dqb_bhardlimit; void* dqb_bsoftlimit; } ;
struct quotause {char* fsname; TYPE_1__ dqblk; struct quotause* next; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int GRPQUOTA ; 
 int MAXLOGNAME ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int USRQUOTA ; 
 scalar_t__ atoi (char*) ; 
 struct quotause* calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 void* cvtblkval (int /*<<< orphan*/ ,char,char*) ; 
 void* cvtinoval (int /*<<< orphan*/ ,char,char*) ; 
 scalar_t__ editit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fchown (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeprivs (struct quotause*) ; 
 long getentry (char*,int) ; 
 int /*<<< orphan*/  getgid () ; 
 int getopt (int,char**,char*) ; 
 struct quotause* getprivs (long,int,char*) ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  hflag ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int mkostemp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  putprivs (long,struct quotause*) ; 
 scalar_t__ readprivs (struct quotause*,int /*<<< orphan*/ ) ; 
 scalar_t__ readtimes (struct quotause*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 scalar_t__ strlen (char*) ; 
 char* strsep (char**,char*) ; 
 scalar_t__ strspn (char*,char*) ; 
 int /*<<< orphan*/  strtoll (char*,char**,int) ; 
 int /*<<< orphan*/  tmpfil ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*,...) ; 
 scalar_t__ writeprivs (struct quotause*,int,char*,int) ; 
 scalar_t__ writetimes (struct quotause*,int,int) ; 

int
main(int argc, char *argv[])
{
	struct quotause *qup, *protoprivs, *curprivs;
	long id, protoid;
	int i, quotatype, range, tmpfd;
	uid_t startuid, enduid;
	uint64_t lim;
	char *protoname, *cp, *endpt, *oldoptarg;
	int eflag = 0, tflag = 0, pflag = 0, ch;
	char *fspath = NULL;
	char buf[MAXLOGNAME];

	if (argc < 2)
		usage();
	if (getuid())
		errx(1, "permission denied");
	quotatype = USRQUOTA;
	protoprivs = NULL;
	curprivs = NULL;
	protoname = NULL;
	while ((ch = getopt(argc, argv, "ughtf:p:e:")) != -1) {
		switch(ch) {
		case 'f':
			fspath = optarg;
			break;
		case 'p':
			if (eflag) {
				warnx("cannot specify both -e and -p");
				usage();
				/* not reached */
			}
			protoname = optarg;
			pflag++;
			break;
		case 'g':
			quotatype = GRPQUOTA;
			break;
		case 'h':
			hflag++;
			break;
		case 'u':
			quotatype = USRQUOTA;
			break;
		case 't':
			tflag++;
			break;
		case 'e':
			if (pflag) {
				warnx("cannot specify both -e and -p");
				usage();
				/* not reached */
			}
			if ((qup = calloc(1, sizeof(*qup))) == NULL)
				errx(2, "out of memory");
			oldoptarg = optarg;
			for (i = 0, cp = optarg;
			     (cp = strsep(&optarg, ":")) != NULL; i++) {
				if (cp != oldoptarg)
					*(cp - 1) = ':';
				if (i > 0 && !isdigit(*cp)) {
					warnx("incorrect quota specification: "
					    "%s", oldoptarg);
					usage();
					/* Not Reached */
				}
				switch (i) {
				case 0:
					strlcpy(qup->fsname, cp,
					    sizeof(qup->fsname));
					break;
				case 1:
					lim = strtoll(cp, &endpt, 10);
					qup->dqblk.dqb_bsoftlimit =
						cvtblkval(lim, *endpt,
						    "block soft limit");
					continue;
				case 2:
					lim = strtoll(cp, &endpt, 10);
					qup->dqblk.dqb_bhardlimit =
						cvtblkval(lim, *endpt,
						    "block hard limit");
					continue;
				case 3:
					lim = strtoll(cp, &endpt, 10);
					qup->dqblk.dqb_isoftlimit =
						cvtinoval(lim, *endpt,
						    "inode soft limit");
					continue;
				case 4:
					lim = strtoll(cp, &endpt, 10);
					qup->dqblk.dqb_ihardlimit =
						cvtinoval(lim, *endpt,
						    "inode hard limit");
					continue;
				default:
					warnx("incorrect quota specification: "
					    "%s", oldoptarg);
					usage();
					/* Not Reached */
				}
			}
			if (protoprivs == NULL) {
				protoprivs = curprivs = qup;
			} else {
				curprivs->next = qup;
				curprivs = qup;
			}
			eflag++;
			break;
		default:
			usage();
			/* Not Reached */
		}
	}
	argc -= optind;
	argv += optind;
	if (pflag || eflag) {
		if (pflag) {
			if ((protoid = getentry(protoname, quotatype)) == -1)
				exit(1);
			protoprivs = getprivs(protoid, quotatype, fspath);
			if (protoprivs == NULL)
				exit(0);
			for (qup = protoprivs; qup; qup = qup->next) {
				qup->dqblk.dqb_btime = 0;
				qup->dqblk.dqb_itime = 0;
			}
		}
		for (; argc-- > 0; argv++) {
			if (strspn(*argv, "0123456789-") == strlen(*argv) &&
			    (cp = strchr(*argv, '-')) != NULL) {
				*cp++ = '\0';
				startuid = atoi(*argv);
				enduid = atoi(cp);
				if (enduid < startuid)
					errx(1,
	"ending uid (%d) must be >= starting uid (%d) when using uid ranges",
						enduid, startuid);
				range = 1;
			} else {
				startuid = enduid = 0;
				range = 0;
			}
			for ( ; startuid <= enduid; startuid++) {
				if (range)
					snprintf(buf, sizeof(buf), "%d",
					    startuid);
				else
					snprintf(buf, sizeof(buf), "%s",
						*argv);
				if ((id = getentry(buf, quotatype)) < 0)
					continue;
				if (pflag) {
					putprivs(id, protoprivs);
					continue;
				}
				for (qup = protoprivs; qup; qup = qup->next) {
					curprivs = getprivs(id, quotatype,
					    qup->fsname);
					if (curprivs == NULL)
						continue;
					curprivs->dqblk = qup->dqblk;
					putprivs(id, curprivs);
					freeprivs(curprivs);
				}
			}
		}
		if (pflag)
			freeprivs(protoprivs);
		exit(0);
	}
	tmpfd = mkostemp(tmpfil, O_CLOEXEC);
	fchown(tmpfd, getuid(), getgid());
	if (tflag) {
		if ((protoprivs = getprivs(0, quotatype, fspath)) != NULL) {
			if (writetimes(protoprivs, tmpfd, quotatype) != 0 &&
			    editit(tmpfil) && readtimes(protoprivs, tmpfil))
				putprivs(0L, protoprivs);
			freeprivs(protoprivs);
		}
		close(tmpfd);
		unlink(tmpfil);
		exit(0);
	}
	for ( ; argc > 0; argc--, argv++) {
		if ((id = getentry(*argv, quotatype)) == -1)
			continue;
		if ((curprivs = getprivs(id, quotatype, fspath)) == NULL)
			exit(1);
		if (writeprivs(curprivs, tmpfd, *argv, quotatype) == 0)
			continue;
		if (editit(tmpfil) && readprivs(curprivs, tmpfil))
			putprivs(id, curprivs);
		freeprivs(curprivs);
	}
	close(tmpfd);
	unlink(tmpfil);
	exit(0);
}