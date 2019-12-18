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
typedef  int /*<<< orphan*/  linebuf ;
typedef  enum md_types { ____Placeholder_md_types } md_types ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  MD_MALLOC 130 
#define  MD_SWAP 129 
#define  MD_VNODE 128 
 unsigned long ULONG_MAX ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 char* fgetln (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  mdname ; 
 int mdnamelen ; 
 scalar_t__ norun ; 
 int /*<<< orphan*/  path_mdconfig ; 
 int run (int*,char*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  run_exitnumber (int) ; 
 int /*<<< orphan*/  run_exitstr (int) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 
 unsigned long strtoul (char*,char**,int) ; 
 unsigned long unit ; 

__attribute__((used)) static void
do_mdconfig_attach_au(const char *args, const enum md_types mdtype)
{
	const char *ta;		/* Type arg. */
	char *linep;
	char linebuf[12];	/* 32-bit unit (10) + '\n' (1) + '\0' (1) */
	int fd;			/* Standard output of mdconfig invocation. */
	FILE *sfd;
	int rv;
	char *p;
	size_t linelen;
	unsigned long ul;

	switch (mdtype) {
	case MD_SWAP:
		ta = "-t swap";
		break;
	case MD_VNODE:
		ta = "-t vnode";
		break;
	case MD_MALLOC:
		ta = "-t malloc";
		break;
	default:
		abort();
	}
	rv = run(&fd, "%s -a %s%s", path_mdconfig, ta, args);
	if (rv)
		errx(1, "mdconfig (attach) exited %s %d", run_exitstr(rv),
		    run_exitnumber(rv));

	/* Receive the unit number. */
	if (norun) {	/* Since we didn't run, we can't read.  Fake it. */
		unit = 0;
		return;
	}
	sfd = fdopen(fd, "r");
	if (sfd == NULL)
		err(1, "fdopen");
	linep = fgetln(sfd, &linelen);
	/* If the output format changes, we want to know about it. */
	if (linep == NULL || linelen <= mdnamelen + 1 ||
	    linelen - mdnamelen >= sizeof(linebuf) ||
	    strncmp(linep, mdname, mdnamelen) != 0)
		errx(1, "unexpected output from mdconfig (attach)");
	linep += mdnamelen;
	linelen -= mdnamelen;
	/* Can't use strlcpy because linep is not NULL-terminated. */
	strncpy(linebuf, linep, linelen);
	linebuf[linelen] = '\0';
	ul = strtoul(linebuf, &p, 10);
	if (ul == ULONG_MAX || *p != '\n')
		errx(1, "unexpected output from mdconfig (attach)");
	unit = ul;

	fclose(sfd);
}