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
typedef  int /*<<< orphan*/  writebuf ;
typedef  char* u_long ;
struct grouplist {scalar_t__ groupid; struct grouplist* next; } ;
struct group {char** gr_mem; int /*<<< orphan*/  gr_gid; } ;
typedef  scalar_t__ gid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int LINSIZ ; 
 char* OPSYS ; 
 int /*<<< orphan*/  _endgrent () ; 
 struct group* _getgrent () ; 
 int /*<<< orphan*/ * _gr_fp ; 
 int /*<<< orphan*/  _setgrent () ; 
 scalar_t__ atol (char*) ; 
 int /*<<< orphan*/  dtable ; 
 int /*<<< orphan*/  err (int,char*,void*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (void*,char*) ; 
 int getopt (int,char**,char*) ; 
 void* groupfile ; 
 void* hostsfile ; 
 struct grouplist* lookup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mstore (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtable ; 
 void* netidfile ; 
 void* optarg ; 
 void* passfile ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*) ; 
 char* strchr (char*,char) ; 
 char* strpbrk (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*,char*,...) ; 
 scalar_t__ yp_get_default_domain (char**) ; 

int
main(int argc, char *argv[])
{
	FILE *gfp, *pfp, *hfp, *nfp;
	char readbuf[LINSIZ];
	char writebuf[LINSIZ];
	struct group *gr;
	struct grouplist *glist;
	char *domain;
	int ch;
	gid_t i;
	char *ptr, *pidptr, *gidptr, *hptr;
	int quiet = 0;

	domain = NULL;
	while ((ch = getopt(argc, argv, "g:p:h:n:d:q")) != -1) {
		switch(ch) {
		case 'g':
			groupfile = optarg;
			break;
		case 'p':
			passfile = optarg;
			break;
		case 'h':
			hostsfile = optarg;
			break;
		case 'n':
			netidfile = optarg;
			break;
		case 'd':
			domain = optarg;
			break;
		case 'q':
			quiet++;
			break;
		default:
			usage();
			break;
		}
	}

	if (domain == NULL) {
		if (yp_get_default_domain(&domain))
			errx(1, "no domain name specified and default \
domain not set");
	}

	if ((gfp = fopen(groupfile, "r")) == NULL) {
		err(1, "%s", groupfile);
	}

	if ((pfp = fopen(passfile, "r")) == NULL) {
		err(1, "%s", passfile);
	}

	if ((hfp = fopen(hostsfile, "r")) == NULL) {
		err(1, "%s", hostsfile);
	}

	if ((nfp = fopen(netidfile, "r")) == NULL) {
		/* netid is optional -- just continue */
		nfp = NULL;
	}

	_gr_fp = gfp;

	/* Load all the group membership info into a hash table. */

	_setgrent();
	while((gr = _getgrent()) != NULL) {
		while(*gr->gr_mem) {
			mstore(mtable, *gr->gr_mem, gr->gr_gid, 0);
			gr->gr_mem++;
		}
	}

	fclose(gfp);
	_endgrent();

	/*
	 * Now parse the passwd database, spewing out the extra
	 * group information we just stored if necessary.
	 */
	while(fgets(readbuf, LINSIZ, pfp)) {
		/* Ignore comments: ^[ \t]*# */
		for (ptr = readbuf; *ptr != '\0'; ptr++)
			if (*ptr != ' ' && *ptr != '\t')
				break;
		if (*ptr == '#' || *ptr == '\0')
			continue;
		if ((ptr = strchr(readbuf, ':')) == NULL) {
			warnx("bad passwd file entry: %s", readbuf);
			continue;
		}
		*ptr = '\0';
		ptr++;
		if ((ptr = strchr(ptr, ':')) == NULL) {
			warnx("bad passwd file entry: %s", readbuf);
			continue;
		}
		*ptr = '\0';
		ptr++;
		pidptr = ptr;
		if ((ptr = strchr(ptr, ':')) == NULL) {
			warnx("bad passwd file entry: %s", readbuf);
			continue;
		}
		*ptr = '\0';
		ptr++;
		gidptr = ptr;
		if ((ptr = strchr(ptr, ':')) == NULL) {
			warnx("bad passwd file entry: %s", readbuf);
			continue;
		}
		*ptr = '\0';
		i = atol(gidptr);

		snprintf(writebuf, sizeof(writebuf), "%s.%s@%s", OPSYS,
							pidptr, domain);

		if (lookup(dtable, writebuf)) {
			if (!quiet)
				warnx("duplicate netid '%s.%s@%s' -- skipping",
						OPSYS, pidptr, domain);
			continue;
		} else {
			mstore(dtable, writebuf, 0, 1);
		}
		printf("%s.%s@%s %s:%s", OPSYS, pidptr, domain, pidptr, gidptr);
		if ((glist = lookup(mtable, (char *)&readbuf)) != NULL) {
			while(glist) {
				if (glist->groupid != i)
					printf(",%lu", (u_long)glist->groupid);
				glist = glist->next;
			}
		}
		printf ("\n");
	}	

	fclose(pfp);

	/*
	 * Now parse the hosts database (this part sucks).
	 */

	while ((ptr = fgets(readbuf, LINSIZ, hfp))) {
		if (*ptr == '#')
			continue;
		if (!(hptr = strpbrk(ptr, "#\n")))
			continue;
		*hptr = '\0';
		if (!(hptr = strpbrk(ptr, " \t")))
			continue;
		*hptr++ = '\0';
		ptr = hptr;
		while (*ptr == ' ' || *ptr == '\t')
			ptr++;
		if (!(hptr = strpbrk(ptr, " \t")))
			continue;
		*hptr++ = '\0';
		snprintf(writebuf, sizeof(writebuf), "%s.%s@%s", OPSYS,
								ptr, domain);
		if (lookup(dtable, (char *)&writebuf)) {
			if (!quiet)
				warnx("duplicate netid '%s' -- skipping",
								writebuf);
			continue;
		} else {
			mstore(dtable, (char *)&writebuf, 0, 1);
		}
		printf ("%s.%s@%s 0:%s\n", OPSYS, ptr, domain, ptr);
	}

	fclose(hfp);

	/*
	 * Lastly, copy out any extra information in the netid
	 * file. If it's not open, just ignore it: it's optional anyway.
	 */

	if (nfp != NULL) {
		while(fgets(readbuf, LINSIZ, nfp)) {
			if (readbuf[0] == '#')
				continue;
			if ((ptr = strpbrk((char*)&readbuf, " \t")) == NULL) {
				warnx("bad netid entry: '%s'", readbuf);
				continue;
			}

			writebuf[0] = *ptr;
			*ptr = '\0';
			if (lookup(dtable, (char *)&readbuf)) {
				if (!quiet)
					warnx("duplicate netid '%s' -- skipping",
								readbuf);
				continue;
			} else {
				mstore(dtable, (char *)&readbuf, 0, 1);
			}
			*ptr = writebuf[0];
			printf("%s",readbuf);
		}
		fclose(nfp);
	}

	exit(0);
}