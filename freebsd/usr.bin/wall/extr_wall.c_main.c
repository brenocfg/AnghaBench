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
struct wallgroup {char const* name; int gid; struct wallgroup* next; } ;
struct utmpx {scalar_t__ ut_type; int /*<<< orphan*/  ut_line; int /*<<< orphan*/  ut_user; } ;
struct passwd {scalar_t__ pw_gid; } ;
struct iovec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
struct group {int gr_gid; char** gr_mem; } ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  LC_CTYPE ; 
 scalar_t__ USER_PROCESS ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  geteuid () ; 
 struct group* getgrgid (scalar_t__) ; 
 struct group* getgrnam (char const*) ; 
 int getopt (int,char**,char*) ; 
 struct passwd* getpwnam (int /*<<< orphan*/ ) ; 
 struct utmpx* getutxent () ; 
 struct wallgroup* grouplist ; 
 int /*<<< orphan*/  makemsg (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  mbuf ; 
 int /*<<< orphan*/  mbufsize ; 
 int nobanner ; 
 char const* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 char* ttymsg (struct iovec*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ttystat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

int
main(int argc, char *argv[])
{
	struct iovec iov;
	struct utmpx *utmp;
	int ch;
	int ingroup;
	struct wallgroup *g;
	struct group *grp;
	char **np;
	const char *p;
	struct passwd *pw;

	(void)setlocale(LC_CTYPE, "");

	while ((ch = getopt(argc, argv, "g:n")) != -1)
		switch (ch) {
		case 'n':
			/* undoc option for shutdown: suppress banner */
			if (geteuid() == 0)
				nobanner = 1;
			break;
		case 'g':
			g = (struct wallgroup *)malloc(sizeof *g);
			g->next = grouplist;
			g->name = optarg;
			g->gid = -1;
			grouplist = g;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;
	if (argc > 1)
		usage();

	for (g = grouplist; g; g = g->next) {
		grp = getgrnam(g->name);
		if (grp != NULL)
			g->gid = grp->gr_gid;
		else
			warnx("%s: no such group", g->name);
	}

	makemsg(*argv);

	iov.iov_base = mbuf;
	iov.iov_len = mbufsize;
	/* NOSTRICT */
	while ((utmp = getutxent()) != NULL) {
		if (utmp->ut_type != USER_PROCESS)
			continue;
		if (ttystat(utmp->ut_line) != 0)
			continue;
		if (grouplist) {
			ingroup = 0;
			pw = getpwnam(utmp->ut_user);
			if (!pw)
				continue;
			for (g = grouplist; g && ingroup == 0; g = g->next) {
				if (g->gid == (gid_t)-1)
					continue;
				if (g->gid == pw->pw_gid)
					ingroup = 1;
				else if ((grp = getgrgid(g->gid)) != NULL) {
					for (np = grp->gr_mem; *np; np++) {
						if (strcmp(*np, utmp->ut_user) == 0) {
							ingroup = 1;
							break;
						}
					}
				}
			}
			if (ingroup == 0)
				continue;
		}
		if ((p = ttymsg(&iov, 1, utmp->ut_line, 60*5)) != NULL)
			warnx("%s", p);
	}
	exit(0);
}